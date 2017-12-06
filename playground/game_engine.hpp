#include "game_engine_interface.hpp"

class game_engine : public game_engine_interface{
	void update(){
		game_engine_interface::recent_status_->clear();
		int sum = 0;
		for (auto o : *game_engine_interface::recent_orders_)
			sum+=o.get_number();
		game_engine_interface::recent_status_->push_back(game_status(sum));
		}
	};
