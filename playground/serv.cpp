#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include "game_order.hpp"
#include "game_status.hpp"
#include "game_engine_interface.hpp"
#include "game_engine.hpp"

using boost::asio::ip::tcp;

typedef std::deque<game_order> game_orders_queue;
typedef std::deque<game_status> game_status_queue;
typedef std::shared_ptr<game_status_queue> game_status_queue_ptr;
typedef std::shared_ptr<game_orders_queue> game_orders_queue_ptr;
typedef std::shared_ptr<game_engine_interface> game_engine_interface_ptr;

class player{
public:
	player():has_turn_(true) {}
	virtual ~player(){}
	virtual void deliver_game_status(const game_status& s) = 0;
	bool has_turn (){return has_turn_;};
	void end_turn() {has_turn_ = false; }
	void new_turn() {has_turn_ = true; }
private:
	bool has_turn_;
	
	};
	
typedef std::shared_ptr<player> player_ptr;
//--------------------------------------------------	
class game_room{
public:
	game_room(){
		//TO DO 
		game_engine_=std::make_shared<game_engine>();
		recent_orders_=std::make_shared<game_orders_queue>();
		recent_status_=std::make_shared<game_status_queue>();
		update_in_progress_=false;
		}
	void join(player_ptr player_){ 
		players_.insert(player_);
		// TO DO 
		}
	void leave (player_ptr player_){
		players_.erase(player_);
		}
	void end_turn(player_ptr player_){
		player_->end_turn();
		bool all_players_ended = true;
		for(auto p : players_){
			if(p->has_turn())
				all_players_ended = false;
			}
		if(all_players_ended){
			update_in_progress_=true;
			update();
			
			}
		}
	void receive_order(const game_order& order){
		if(!update_in_progress_){
			recent_orders_->push_back(order);
			std::cout<<"TEST" <<std::endl;
			std::cout.write(order.body(), 4);
		}
		}
	void deliver_game_status(){
		while(!recent_status_->empty()){
			game_status gst = recent_status_->front();
			recent_status_->pop_front();
			for(auto p : players_){
				p->deliver_game_status(gst);
				}
			}
		}
	//TO DO
	void update(){
		game_engine_->take_orders_queue(recent_orders_);
		game_engine_->update();		
		recent_status_=game_engine_->get_status();
		deliver_game_status();
		recent_orders_->clear();
		update_in_progress_=false;
		}
	bool update_in_progress(){
		return update_in_progress_;
		}
		
private:
	std::set<player_ptr> players_;
	game_orders_queue_ptr recent_orders_;
	game_status_queue_ptr recent_status_;
	game_engine_interface_ptr game_engine_;
	bool update_in_progress_;
	};
//-----------------------------------	
class game_session: public player, public std::enable_shared_from_this<game_session>{
public:
	game_session(tcp::socket socket, game_room& room) : socket_(std::move(socket)), room_(room){}
	void start(){
		room_.join(shared_from_this());
		do_read_header();
		}
	void deliver_game_status(const game_status& s){
		bool write_in_progress = !write_status_queue_.empty();
		write_status_queue_.push_back(s);
		if(!write_in_progress){
			do_write();
			}	
		}
private:
	void do_read_header(){
		auto self(shared_from_this());
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_order_.data(), game_order::header_length),
			[this, self](boost::system::error_code ec, std::size_t /*length*/){
				if(!ec && read_order_.decode_header())
					{do_read_body();}
				else{
					room_.leave(shared_from_this());
					}
			});
	}//do_read_header()
	
	void do_read_body(){
		auto self(shared_from_this());
		boost::asio::async_read(socket_,
		boost::asio::buffer(read_order_.body(), read_order_.body_length()),
		[this, self](boost::system::error_code ec, std::size_t /*length*/){
			if(!ec){
				if(read_order_.turn_ended() && !room_.update_in_progress()){
					room_.end_turn(shared_from_this());
					do_read_header();
					} 
				else{
					if(!room_.update_in_progress())
						room_.receive_order(read_order_);
						do_read_header();
					}
				}
				else{
					room_.leave(shared_from_this());
				}
		});
	}//do_read_body()
	void do_write(){
		auto self(shared_from_this());
		boost::asio::async_write(socket_,
		boost::asio::buffer(write_status_queue_.front().data(),
			write_status_queue_.front().length()),
			[this, self] (boost::system::error_code ec, std::size_t /*length*/){
				if(!ec){
					//TEST
					std::cout<<"server send status";
					write_status_queue_.pop_front();
					if(!write_status_queue_.empty()){
						do_write();
						}
					else{
							room_.leave(shared_from_this());
						}
					}
			});
		}//do_write()
	tcp::socket socket_;
	game_room& room_;
	game_status_queue write_status_queue_;
	game_order read_order_;

	};
//-----------------------------------
class game_server{
public:
	game_server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)
		:acceptor_(io_service, endpoint), socket_(io_service) { do_accept(); }
private:
	void do_accept(){
		acceptor_.async_accept(socket_,[this] (boost::system::error_code ec){
			if(!ec){
					std::make_shared<game_session>(std::move(socket_), room_)->start();
				}
			
			do_accept();
			});
		}
	tcp::acceptor acceptor_;
	tcp::socket socket_;
	game_room room_;
	};

int main (int argc, char* argv[]){
	
	try{
		if(argc < 2){
			std::cerr << "Usage: <port>";
			}
		boost::asio::io_service io_service;
		tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[1]));
		game_server server (io_service, endpoint);
		io_service.run();
		}
	catch (std::exception& e){
			std::cerr << "Exception: " <<e.what() <<"\n";
		}
	}
