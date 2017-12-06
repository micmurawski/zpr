#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "game_order.hpp"
#include "game_status.hpp"

using boost::asio::ip::tcp;

typedef std::deque<game_order> orders_queue;

class game_client{
public:
	game_client(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator):
	io_service_(io_service), socket_(io_service) {
		do_connect(endpoint_iterator);
	}
	void write(const game_order& ord){
		io_service_.post( 
			[this, ord]() {
				bool write_in_progress = !write_orders_.empty();
				write_orders_.push_back(ord);
				if(!write_in_progress){
					do_write();
					}
				});
		};	
	void close(){
		io_service_.post([this](){socket_.close();});
		};
private:
	void do_connect(tcp::resolver::iterator endpoint_iterator){
		boost::asio::async_connect(socket_, endpoint_iterator,
		[this](boost::system::error_code ec, tcp::resolver::iterator){
			if (!ec){
				do_read_header();
				}
			});
		}
	void do_read_header(){
		boost::asio::async_read(socket_, boost::asio::buffer(read_status_.body(), read_status_.body_length()), 
		[this](boost::system::error_code ec, std::size_t /*length*/){
		if(!ec && read_status_.decode_header()){
			do_read_body();
			}
		else{
			socket_.close();
			}
			});
		}
	void do_read_body(){
		boost::asio::async_read(socket_,
		boost::asio::buffer(read_status_.body(), read_status_.body_length()),
		[this](boost::system::error_code ec, std::size_t /* length */){
			if (!ec){
				//FOR TESTING
				std::cout<<"TEST";
				std::cout.write(read_status_.data(), 8);
				std::cout<< "\n";
				do_read_header();
				}
			else{
				socket_.close();
				}
			});
		}
	void do_write(){
		boost::asio::async_write(socket_,
		boost::asio::buffer(write_orders_.front().data(),
		write_orders_.front().length()),
		[this] (boost::system::error_code ec, std::size_t /* length*/){
			if (!ec){
				write_orders_.pop_front();
				if(!write_orders_.empty()){
					do_write();
					}
					else{
						socket_.close();
						}
				}
			});
		}
			
private:
	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	game_status read_status_;
	orders_queue write_orders_;
	};
//-------------------------------------

int main(int argc, char* argv[]){
	try{
		if(argc != 3){
			std::cerr <<"Usage:chat_client <host> <port>\n";
			return 1;
			}
		boost::asio::io_service io_service;
		
		tcp::resolver resolver(io_service);
		auto endpoint_iterator = resolver.resolve({argv[1], argv[2]});
		game_client c(io_service, endpoint_iterator);
		
		std::thread t([&io_service](){io_service.run();});
		//TEST
		c.write(game_order(5));
		c.write(game_order(6));
		c.write(game_order(7));
		c.write(game_order(1111));
		while(char c = std::cin.get()){
			if (c=='x')
				break;
			}
		c.close();
		t.join();
		} catch( std::exception& e){
			std::cerr<< "Exception: " <<e.what() <<"\n";
			}
		
	return 0;
	}
