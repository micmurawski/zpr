#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "game_object.hpp"
/**
 * \class MapPoint
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
 	* \param[in] point_id_ pozycja na mapie budynku, domyślnie 0
	*
 	*/
    Building(int point_id_=0): point_id_(0){}
	/**
 	* Funkcja zwracająca położenie w węźle mapy
	* \return węzeł mapy
 	*/
	unsigned int getMapPointId(){return point_id_;}

    virtual std::string toString();
    virtual void loadFromString (std::string data);
    //used to determine type in GameObjectsFactory
    virtual unsigned int getType(){return ID_;}
    //used to create objects in GameObjectsFactory
    static std::shared_ptr<GameObject> create();
    //ID needed for ObjectFactory
    static unsigned int ID_;
private:
	unsigned int point_id_;
};

#endif //BUILDING_HPP
