#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "game_object.hpp"
/**
 * \class Building
 *
 * Definicja klasy Building, która realizuje budynki. Dziedziczy wirtualnie po klasie GameObject
 * \author $Author: Marcin Brzykcy, Michał Murawski $
 *
 */
#include <memory>

class Building : public GameObject{
public:
	/**
 	* Konstruktor klasy
 	*
 	* \param point_id_ pozycja na mapie budynku, domyślnie 0
	*
 	*/
    Building(int point_id=0): point_id_(point_id){}
	/**
 	* Funkcja zwracająca położenie w węźle mapy
	* \return węzeł mapy
 	*/
	unsigned int getMapPointId(){return point_id_;}
	/**
 	* Funkcja dokonująca serializacji obiektu do ciągu znaków, aby móc go potem przesłać
	* \return obiekt przekonwertowany do std::string
 	*/
    virtual std::string toString();
    /**
 	* Funkcja odczytująca obiekt z std::string
	* \param data przesłany obiekt
 	*/
    virtual void loadFromString (std::string data);

private:
	unsigned int point_id_;
};

#endif //BUILDING_HPP
