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
		case MoveOrder::type_id : {
			shared_ptr<MoveOrder> move = make_shared<MoveOrder>();
			strncat(move->getData(),  game_sendable.getData(), game_sendable.getLength());
			move->decode();
			return move;
			break;
			}
		case  BuildOrder::type_id : {
			shared_ptr<BuildOrder> build = make_shared<BuildOrder>();
			strncat(build->getData(),  game_sendable.getData(), game_sendable.getLength());
			build->decode();
			return build;
			break;
			}
		case  CreateShipOrder::type_id : {
			shared_ptr<CreateShipOrder> create = make_shared<CreateShipOrder>();
			strncat(create->getData(),  game_sendable.getData(), game_sendable.getLength());
			create->decode();
			return create;
			break;
			}
		}
	}
private:
	
};

#endif //ORDER_DECODER_HPP
