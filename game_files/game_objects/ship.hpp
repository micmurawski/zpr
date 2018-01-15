#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <memory>
#include <string>
#include "game_object.hpp"


/**
 * \class Ship
 *
 * Definicja klasy Ship, która realizuje obiekty statków w grze. Dziedziczy wirtualnie po klasie GameObject
 * \author $Author: Marcin Brzykcy $
 *
 */

class Ship : public GameObject{
public:
	/**
 	* Konstruktor klasy
 	*
 	* \param[in] id identyfikator
 	* \param[in] map_point_id pozycja na mapie.
	* \param[in] hp_ poziom życia
 	* 
 	*/
	Ship(unsigned int id=0, unsigned int map_point_id=0): hp_(80), id_(id), map_point_id_(map_point_id) {}
	/**
 	* Funkcja zmieniająca poziom życia
 	*
 	* \param[in] hp ilość dodawanego życia
 	* 
 	*/
	virtual void modifyHP(int hp);
	/**
 	* Funkcja zwracająca obrażenia statku
 	* \return zwraca obrażenia 
 	*/
	virtual int getDamage() {return 10;}
	/**
 	* Funkcja zwracająca reprezentacje obiektu w stringu
 	* \return zwraca string reprezentujący obiekt
 	*/
	virtual std::string toString(unsigned int player_id = 0);
	/**
 	* Funkcja przypisująca pola dla obiektu z zadanego stringa
 	*/
	virtual void loadFromString (std::string data);
	/**
 	* Funkcja zwracająca liczbę reprezentowaną jako typ w fabryce obiektów GameObjectFactory
 	* \return typ
 	*/
	virtual unsigned int getType();
	/**
 	* Funkcja zwracająca wskaźnik na GameObject wykorzystywane do utworzenia instacji obiektu w GameObjectFactory
 	* \return wkaźnik na GameObject
 	*/
	static std::shared_ptr<GameObject> create();
	//ID is needed for ObjectFactory
	static unsigned int ID_;
	/**
 	* Funkcja zwracająca położenie na mapie
 	* \return zwraca położenie na mapie
 	*/
	unsigned int getMapPointId(){return map_point_id_;}
    /**
 	* Funkcja zwracająca identyfikator obiektu
 	* \return zwraca indentyfikator 
 	*/
    unsigned int getId(){return id_;}

private:
	unsigned int hp_;
	//map_point_id is ship location
	unsigned int map_point_id_;
	//id of the individual ship
	unsigned int id_;

	};
	

#endif //SHIP_HPP
