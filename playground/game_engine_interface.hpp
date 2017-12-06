#ifndef GAME_ENGINE_INTERFACE_HPP
#define GAME_ENGINE_INTERFACE_HPP

#include "game_order.hpp"
#include "game_status.hpp"

typedef std::deque<game_order> game_orders_queue;
typedef std::deque<game_status> game_status_queue;
typedef std::shared_ptr<game_status_queue> game_status_queue_ptr;
typedef std::shared_ptr<game_orders_queue> game_orders_queue_ptr;

class game_engine_interface{
public:
	virtual void update()=0;
	game_status_queue_ptr get_status(){return recent_status_;}
	void take_orders_queue(game_orders_queue_ptr orders){recent_orders_=orders;}
protected:
	game_orders_queue_ptr recent_orders_;
	game_status_queue_ptr recent_status_;
	
};
#endif
