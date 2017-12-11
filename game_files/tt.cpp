#include "game_order.hpp"
#include "building.hpp"
#include <cstdio>
#include <iostream>
#include <vector>
#include "order_decoder.hpp"

using namespace std;

int main(){
	OrderDecoder decoder;
	decoder.decode("#1#12#11#14#15");
	cout<<endl <<decoder.move_orders_[0]->toString();
	decoder.decode("#3#23#433");
	cout<<endl <<decoder.create_ship_orders_[0]->toString();
}
