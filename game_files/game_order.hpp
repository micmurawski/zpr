#ifndef GAME_ORDER_HPP
#define GAME_ORDER_HPP
#include "game_sendable.hpp"
#include "typedefs.hpp"
#include <vector>
#include <memory>
#include "game_engine.hpp"

class GameOrder : public GameSendable{
public:
	enum {id_length = 6};
	virtual void encode() = 0;
	virtual bool decode() = 0;
	virtual void execute(GameEngine& game) = 0;

};

class MoveOrder: public GameOrder{
public:
	enum {type_id= 1};
	MoveOrder():start_point_id_(0), destination_id_(0) {ship_id_vector_ = std::make_unique<std::vector<unsigned int>>();}
	MoveOrder(unsigned int start_point_id, unsigned int destination_id, const std::vector<unsigned int>& ship_id_vector):
	start_point_id_(start_point_id), destination_id_(destination_id){ship_id_vector_ = std::make_unique<std::vector<unsigned int>> (ship_id_vector);}
	virtual void encode();
	virtual bool decode();
	unsigned int getStartPoint() const {return start_point_id_;}
	unsigned int getDestination() const {return destination_id_;}
	const ship_vector_uptr& getShipVector() const {return ship_id_vector_;}
	virtual void execute (GameEngine& game);
private:
	unsigned int start_point_id_;
	unsigned int destination_id_;
	ship_vector_uptr ship_id_vector_;
};

class BuildOrder: public GameOrder{
public:
	BuildOrder(unsigned int point_id = 0, unsigned int building_type = 0): point_id_(point_id), building_type_(building_type){}
	enum {type_id= 2};
	virtual void encode();
	virtual bool decode();
	unsigned int getPointId(){return point_id_;}
	unsigned int getBuildingType(){return building_type_;}
	virtual void execute (GameEngine& game);
	
private:
	unsigned int point_id_;
	unsigned int building_type_;
};

class CreateShipOrder: public GameOrder{
public:
	enum {type_id= 3};
	CreateShipOrder(unsigned int point_id = 0, unsigned int ship_type = 0): point_id_(point_id), ship_type_(ship_type){}
	virtual void encode();
	virtual bool decode();
	unsigned int getPointId();
	unsigned int getShipType();
	virtual void execute (GameEngine& game);
private:
	unsigned int point_id_;
	unsigned int ship_type_;
};

#endif //GAME_ORDER_HPP
