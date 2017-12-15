#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <string>


class GameObject{
	public:
	virtual std::string toString(unsigned int player_id = 0) {return "";}
	virtual void loadFromString (std::string data) {}
	virtual unsigned int getType() {return 0;}
	unsigned int player_id_;
};

#endif
