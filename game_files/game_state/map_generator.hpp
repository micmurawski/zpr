#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

#include "../game_state/game_state.hpp"

class MapGenerator
{
public:
    MapGenerator(unsigned int alfa_var, unsigned int point_nr):
         point_nr_(point_nr){}
    vector<map_point_ptr> generate ();
private:
    void createPointRec(unsigned int id, float alfa, float alfa_var, int x, int y, unsigned int r, int depth);
    unsigned int getId(){return id++;}
    bool intersection(int x, int y);
    unsigned int r_;
    unsigned int id;
    unsigned int point_nr_;
    vector<map_point_ptr> map_points_;
};

#endif // MAPGENERATOR_HPP