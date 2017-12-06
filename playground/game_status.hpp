#ifndef GAME_STATUS_HPP
#define GAME_STATUS_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "game_sendable.hpp"


class game_status : public game_sendable{
public:
	game_status() {}
	//for testing
	game_status(int sum){
		body_length(4);
		encode_header();
		char t[] = "bbbb";
		//t = "bbbb";//(std::to_string(sum)).c_str();
		std::sprintf(body(), "bbbb");
		}
};

#endif 
