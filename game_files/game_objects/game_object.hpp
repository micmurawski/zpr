#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <string>
/**
 * \class GameObject
 *
 * Definicja klasy wirtualnej GameObject(Intefejs) po której dziedziczą wszystkie realizowane obiekty w grze
 * \author $Author: Marcin Brzykcy, Michał Murawski $
 *
 */

class GameObject{
	public:
	/**
 	* Funkcja zwracająca reprezentacje obiektu w stringu
 	* \return zwraca string reprezentujący obiekt
 	*/	
	virtual std::string toString(unsigned int player_id = 0) {return "";}
	/**
 	* Funkcja zwracająca liczbę reprezentowaną jako typ w fabryce obiektów GameObjectFactory
 	* \return typ
 	*/
	virtual void loadFromString (std::string data) {}
	/**
 	* Funkcja zwracająca liczbę reprezentowaną jako typ w fabryce obiektów GameObjectFactory
 	* \return typ
 	*/
	virtual unsigned int getType() {return 0;}
	unsigned int player_id_;
};

#endif
