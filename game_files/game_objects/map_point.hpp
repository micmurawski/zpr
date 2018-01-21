#ifndef MAP_POINT_HPP
#define MAP_POINT_HPP

#include <vector>
#include <memory>
#include "resources.hpp"
#include "building.hpp"
#include "resources.hpp"
#include <memory>
#include "game_object.hpp"
#include "resources.hpp"
#include <vector>
/**
 * \class MapPoint
 *
 * Definicja klasy MapPoint, która realizuje mape gry. Dziedziczy wirtualnie po klasie GameObject
 * \author $Author: Marcin Brzykcy, Michał Murawski $
 *
 */
class MapPoint : public GameObject{
public:
	/**
 	* Konstruktor domyślny klasy
 	*
 	*/
	MapPoint(){};
	/**
 	* Konstruktor klasy
 	*
 	* \param id  identyfikator węzła mapy
	* \param connections - wektor numerów id połączonych punktów
	* \param x położenie na osi x
	* \param y położenie na osi y
	* \param resources zasoby przechowywane na punkcie
	*
 	*/
	MapPoint(int id, const std::vector<unsigned int>& connections, int x, int y, Resources resources): 
	id_(id), connections_(connections), x_(x), y_(y) {resources_ = resources;}
	/**
 	* Konstruktor klasy
 	*
 	* \param id  identyfikator węzła mapy
	* \param x położenie na osi x
	* \param y położenie na osi y
	* \param resources zasoby przechowywane na punkcie
	*
 	*/
	MapPoint(int id,  int x, int y, Resources resources): 
	id_(id),  x_(x), y_(y) {resources_ = resources;}
	
	unsigned int getId() const {return id_;} 
	unsigned int getX() const {return x_;} 
	unsigned int getY() const {return y_;} 
    int getMetal() const {return resources_.metal_;}
	const std::vector<unsigned int>& getConnections() {return connections_;}
    void addConnection(unsigned int id){connections_.push_back(id);};
	/**
 	* Funkcja zwracająca reprezentacje obiektu w stringu
 	* \return zwraca string reprezentujący obiekt
 	*/	
	virtual std::string toString(unsigned int player_id = 0);
	/**
 	* Funkcja zwracająca liczbę reprezentowaną jako typ w fabryce obiektów GameObjectFactory
 	* \return typ
 	*/
	virtual void loadFromString (std::string data);

	/**
 	* Funkcja zwracająca położenie na mapie
 	* \return zwraca położenie na mapie
 	*/
	static unsigned int ID_;
		
		
private:
	//id właściciela
	unsigned int owner_id;
	//id pojedynczego punktu
	unsigned int id_;
	public:
	//wektor połączonych punktów
	std::vector<unsigned int> connections_;
	unsigned int x_;
	unsigned int y_;	
	Resources resources_;
	};
	
#endif //MAP_POINT_HPP


