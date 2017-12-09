#include "game_order.hpp"
#include "building.hpp"
#include <cstdio>
#include <iostream>
#include <vector>

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
	MoveOrder m;
	strncpy(m.getData(), move.getData(), move.getBodyLength()+GameOrder::header_length);
	cout<<endl;
	cout.write(m.getData(), move.getBodyLength()+GameOrder::header_length);
	cout <<endl;
	m.decode();
	cout<< endl <<m.getStartPoint() <<endl <<m.getDestination() <<endl;
	for (auto id : *m.getShipVector()){
		cout<<endl <<id ;
		}
	
	return 0;
}
