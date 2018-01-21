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
 	* \param metal ilośc przechowywanych zasobów
 	*/
	Resources(int metal=0) : metal_(metal){};
	unsigned int metal_;

	/**
 	* Funkcja zwracająca reprezentacje obiektu w std::string
 	* \return zwraca std::string reprezentujący obiekt
 	*/
    virtual std::string toString();
	/**
 	* Funkcja zwracająca liczbę reprezentowaną jako typ w fabryce obiektów GameObjectFactory
 	* \param reprezentacja obiektu w std::string
 	*/
	virtual void loadFromString (std::string data);


};

#endif //RESOURCES_HPP
