#ifndef ORDER_DECODER_HPP
#define ORDER_DECODER_HPP

#include <map>
#include <memory>
#include "../typedefs.hpp"
#include "game_order.hpp"
#include <regex>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "../get_regex_function.hpp"

using namespace std;

class OrderDecoder{
public:
    void decode(string orders){
	int i =10;

    std::vector<std::string> vec;
	while(orders.size()>0){
	string order = orders.substr(orders.find("<order>")+7, orders.find("</order>")-7);
	vec.push_back(order);
    orders = orders.substr(orders.find("</order>")+8);
		}
	for(auto order : vec){
		//cout<<endl <<order;
		
		string s1 = getRegex(order, "(?<=<move>)(.*)(?=</move>)");
		string s2 = getRegex(order, "(?<=<build>)(.*)(?=</build>)");
		string s3 = getRegex(order, "(?<=<create>)(.*)(?=</create>)");
		if(s1.length()>0){
			cout<<endl<<s1;
			
			shared_ptr<MoveOrder> ptr  = make_shared<MoveOrder>(s1);
			move_orders_.push_back(ptr);
			}
		if(s2.length()>0){
			
			cout<<endl<<s2;
			
			shared_ptr<CreateShipOrder> ptr  = make_shared<CreateShipOrder>(s2);
			create_ship_orders_.push_back(ptr);
			}
		if(s3.length()>0){
			
			cout<<endl<<s3;
			
			shared_ptr<BuildOrder> ptr  = make_shared<BuildOrder>(s3);
			build_orders_.push_back(ptr);
			
			}
			
		}
	}
	
	void clear(){
		move_orders_.clear();
		create_ship_orders_.clear();
		build_orders_.clear();
		}
	vector<shared_ptr<MoveOrder>> move_orders_;
	vector<shared_ptr<CreateShipOrder>> create_ship_orders_;
	vector<shared_ptr<BuildOrder>> build_orders_;
};

#endif //ORDER_DECODER_HPP
