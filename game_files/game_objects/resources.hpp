#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "game_object.hpp"
#include <string>
#include <memory>

/**
 * \class Resources
 *
 * Definicja klasy Resources, która realizuje zasoby gracza. Dziedziczy wirtualnie po klasie GameObject
 * \author $Author: Marcin Brzykcy, Michał Murawski $
 *
 */
class Resources : public GameObject{
	public:
	/**
 	* Konstruktor klasy
 	*
 	* \param[in] metl ilośc przechowywanych zasobów
 	*/
	Resources(int metal=0) : metal_(metal){};
	unsigned int metal_;
	
	//this method is used if we want to get string containing 
	//only data of variables, withoud additional information
	std::string toStringDataOnly();
	/**
 	* Funkcja zwracająca reprezentacje obiektu w stringu
 	* \return zwraca string reprezentujący obiekt
 	*/
    virtual std::string toString();
	/**
 	* Funkcja zwracająca liczbę reprezentowaną jako typ w fabryce obiektów GameObjectFactory
 	* \return typ
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
	/**
 	* Funkcja zwracająca położenie na mapie
 	* \return zwraca położenie na mapie
 	*/
	static unsigned int ID_;
};

#endif //RESOURCES_HPP
