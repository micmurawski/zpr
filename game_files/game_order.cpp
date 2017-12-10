#include "game_order.hpp"
#include "typedefs.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>

void MoveOrder::encode(){
	setBodyLength((2+ship_id_vector_->size())*GameOrder::id_length); //2 for destination_point_id + starting_point_id
	setType(MoveOrder::type_id);
	char temp[getBodyLength()+1];
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
	std::memcpy(getBody(), temp, getBodyLength());
	encodeHeader();
	}
	
bool MoveOrder::decode(){
	//using decode_header() from game_sendable base class to get
	//body length
	decodeHeader();
	//decoding start point id from body
	char start_point_id [GameOrder::id_length] = "";
	strncat(start_point_id, getBody(), GameOrder::id_length);
	start_point_id_ = atoi(start_point_id);
	//decoding destination id from body
	char destination_id [GameOrder::id_length] = "";
	strncat(destination_id, getBody()+GameOrder::id_length, GameOrder::id_length);
	destination_id_ = atoi(destination_id);
	//decoding ship ids in loop from body
	ship_id_vector_->clear();
	unsigned int i=GameOrder::id_length*2;
	while(i<getBodyLength()){
		char ship_id [GameOrder::id_length]="";
		strncat(ship_id, getBody()+i, GameOrder::id_length);
		i +=GameOrder::id_length;
		ship_id_vector_->push_back(atoi(ship_id));
		}
}

void MoveOrder::execute(GameEngine& game){
		//game.move(...)
	}
	
void BuildOrder::encode(){
	setBodyLength(2*GameOrder::id_length);
	setType(BuildOrder::type_id);
	char temp[getBodyLength()+1];
	//copying point id and type of building into char[] temp
	std::sprintf(temp, "%*d%*d", GameOrder::id_length, point_id_, GameOrder::id_length, building_type_);
	//copying temp into body
	std::memcpy(getBody(), temp, getBodyLength());
	encodeHeader();
	}
	
bool BuildOrder::decode(){
	//using decode_header() from game_sendable base class to get
	//body length
	decodeHeader();
	//decoding start point id from body
	char point_id [GameOrder::id_length] = "";
	strncat(point_id, getBody(), GameOrder::id_length);
	point_id_ = atoi(point_id);
	//decoding building type from body
	char building_type[GameOrder::id_length] = "";
	strncat(building_type, getBody()+GameOrder::id_length, GameOrder::id_length);
	building_type_ = atoi(building_type);
	}
void BuildOrder::execute(GameEngine& game){
		//game.buid(...)
	}

void CreateShipOrder::encode(){
	setBodyLength(2*GameOrder::id_length);
	setType(CreateShipOrder::type_id);
	char temp[getBodyLength()+1];
	//copying point id and type of ship into char[] temp
	std::sprintf(temp, "%*d%*d", GameOrder::id_length, point_id_, GameOrder::id_length, ship_type_);
	//copying temp into body
	std::memcpy(getBody(), temp, getBodyLength());
	encodeHeader();
	}
	
bool CreateShipOrder::decode(){
	//using decode_header() from game_sendable base class to get
	//body length
	decodeHeader();
	//decoding  point id from body
	char point_id [GameOrder::id_length] = "";
	strncat(point_id, getBody(), GameOrder::id_length);
	point_id_ = atoi(point_id);
	//decoding ship type from body
	char ship_type[GameOrder::id_length] = "";
	strncat(ship_type, getBody()+GameOrder::id_length, GameOrder::id_length);
	ship_type_ = atoi(ship_type);
	}
void CreateShipOrder::execute(GameEngine& game){
		//game.create_ship(...)
	}
