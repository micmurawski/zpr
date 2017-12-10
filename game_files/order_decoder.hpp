#ifndef ORDER_DECODER_HPP
#define ORDER_DECODER_HPP

#include <map>
#include <memory>
#include "typedefs.hpp"
#include "game_order.hpp"
#include "game_sendable.hpp"

using namespace std;

class OrderDecoder{
public:
	shared_ptr<GameOrder> decode(GameSendable& game_sendable){
		game_sendable.decodeHeader();
		unsigned int type = game_sendable.getType();
		switch(type){
		case MoveOrder::type_id :
			shared_ptr<MoveOrder> move = make_shared<MoveOrder>();
			strncat(move->getData(),  game_sendable.getData(), game_sendable.getLength());
			move->decode();
			return move;
		break;

		//default:
		//
		//break;
		}
	}
private:
	
};

#endif //ORDER_DECODER_HPP
