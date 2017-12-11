#include "game_object.hpp"
class Ship : public GameObject{
public:
	virtual void modifyHP(int hp) {
		hp_ +=hp;
		if(hp_<0)
			hp_ = 0;
		}
	virtual int getDamage() {return 10;}
	Ship(int id): hp_(80), id_(id) {}
private:
	unsigned int hp_;
	unsigned int id_;
	};
