#include "game_order.hpp"
#include "building.hpp"
#include <cstdio>
#include <iostream>
#include <vector>
#include "order_decoder.hpp"

using namespace std;

int main(){
	std::vector<unsigned int> s;
	s.push_back(static_cast<unsigned int>(1234));
	s.push_back(32);
	s.push_back(2);
	s.push_back(4423);
	s.push_back(1221);
	MoveOrder move (2, 34, s);
	move.encode();
	cout<<GameOrder::header_length <<" ";
	cout<<move.getBodyLength() <<"\n";
	cout.write(move.getData(), move.getBodyLength()+GameOrder::header_length);
	cout <<'\n';
	cout <<"test 2";
	GameSendable recived;
	strncpy(recived.getData(), move.getData(), move.getBodyLength()+GameOrder::header_length);
	OrderDecoder decoder;
	shared_ptr<GameOrder>g = decoder.decode(recived);
	shared_ptr<MoveOrder>p = dynamic_pointer_cast<MoveOrder> (g);
	cout<<endl <<(p)->getDestination() <<endl;
	cout<<endl <<(p)->getStartPoint() <<endl;
	return 0;
}
