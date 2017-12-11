#ifndef ORDER_DECODER_HPP
#define ORDER_DECODER_HPP

#include <map>
#include <memory>
#include "typedefs.hpp"
#include "game_order.hpp"
#include <regex>

using namespace std;

class OrderDecoder{
public:
	void decode(string order){	
	//erasing first "#" from the beggining of string
	string s = order.substr(1, s.size());
	//spliting string s into two substrings, first is type of object 
	//and second is data used to create GameOrder of this type
	regex r("#");
	smatch m; 
	regex_search(s, m, r); 
	int split_on = m.position();
	string type = (s.substr(0, split_on));
	string data  = s.substr(split_on + m.length()); 
	switch(std::stoi(type)){
		case MoveOrder::type:{
			shared_ptr<MoveOrder> ptr  = make_shared<MoveOrder>(data);
			move_orders_.push_back(ptr);
			break;
			}
		case CreateShipOrder::type:{
			shared_ptr<CreateShipOrder> ptr = make_shared<CreateShipOrder>(data);
			create_ship_orders_.push_back(ptr);
			break;
			}
		}	
	}
	vector<shared_ptr<MoveOrder>> move_orders_;
	vector<shared_ptr<CreateShipOrder>> create_ship_orders_;
};

#endif //ORDER_DECODER_HPP
