#include "game_order.hpp"
#include "typedefs.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>

void MoveOrder::encode(){
	body_length((2+ship_id_vector_->size())*GameOrder::id_length); //2 for destination_point_id + starting_point_id
	SetType(1);
	char temp[body_length()+1];
	//copying starting point id and destination point id into char[] temp
	char temp1[2*GameOrder::id_length+1];
	std::sprintf(temp1, "%*d%*d", GameOrder::id_length, start_point_id_, GameOrder::id_length, destination_id_);
	strncpy(temp, temp1, GameOrder::id_length*2);
	//copying ships' id from vector into char[] temp
	int i=2;
	for (auto id : *ship_id_vector_){
		char temp2[GameOrder::id_length+1];
		sprintf(temp2, "%*d", GameOrder::id_length, id);
		strncpy(temp+(GameOrder::id_length)*i, temp2, GameOrder::id_length);
		++i;
	}
	//copying temp into body
	std::memcpy(body(), temp, body_length());
	encode_header();
	}
	
bool MoveOrder::decode(){
	//using decode_header() from game_sendable base class to get
	//body length
	decode_header();
	//decoding start point id from body()
	char start_point_id [GameOrder::id_length] = "";
	strncat(start_point_id, body(), GameOrder::id_length);
	start_point_id_ = atoi(start_point_id);
	//decoding destination id from body()
	char destination_id [GameOrder::id_length] = "";
	strncat(destination_id, body()+GameOrder::id_length, GameOrder::id_length);
	destination_id_ = atoi(destination_id);
	//decoding ship ids in loop from body()
	ship_id_vector_->clear();
	unsigned int i=GameOrder::id_length*2;
	while(i<body_length()){
		char ship_id [GameOrder::id_length]="";
		strncat(ship_id, body()+i, GameOrder::id_length);
		i +=GameOrder::id_length;
		ship_id_vector_->push_back(atoi(ship_id));
		}
	
	}

