#ifndef GAME_ORDER_HPP
#define GAME_ORDER_HPP
#include "../typedefs.hpp"
#include <vector>
#include <memory>
#include "../game_engine/game_engine.hpp"

typedef std::unique_ptr<std::vector<unsigned int>> ship_vector_uptr;



class GameOrder{
public:
  virtual std::string toString() const=0;
  virtual int type() const = 0;

};

class MoveOrder : public GameOrder{
public:
    enum {type_id = 1};
	MoveOrder():start_point_id_(0), destination_id_(0) {ship_id_vector_ = std::make_unique<std::vector<unsigned int>>();}
	MoveOrder(unsigned int start_point_id, unsigned int destination_id, const std::vector<unsigned int>& ship_id_vector):
	start_point_id_(start_point_id), destination_id_(destination_id){ship_id_vector_ = std::make_unique<std::vector<unsigned int>> (ship_id_vector);}
	MoveOrder(std::string data);
    std::string toString() const;
	unsigned int getStartPoint() const {return start_point_id_;}
	unsigned int getDestination() const {return destination_id_;}
	const ship_vector_uptr& getShipVector() const {return ship_id_vector_;}
    int type() const{return MoveOrder::type_id;}
private:
	unsigned int start_point_id_;
	unsigned int destination_id_;
    ship_vector_uptr ship_id_vector_;
};

class BuildOrder : public GameOrder{
public:
    BuildOrder(unsigned int point_id = 0): point_id_(point_id){}
    BuildOrder(std::string data);
	enum {type_id= 2};
    unsigned int getPointId() const {return point_id_;}
    std::string toString() const;
    int type() const {return BuildOrder::type_id;}
private:
    unsigned int point_id_;
};

class CreateShipOrder: public GameOrder{
public:
    enum {type_id=3};
    CreateShipOrder(unsigned int point_id = 0): point_id_(point_id){}
    std::string toString() const;
	CreateShipOrder(std::string data);
    unsigned int getPointId() const {return point_id_;}
    int type() const {return CreateShipOrder::type_id;}
private:
	unsigned int point_id_;
};

#endif //GAME_ORDER_HPP
