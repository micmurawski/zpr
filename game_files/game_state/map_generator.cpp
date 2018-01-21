#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>

#include "map_generator.hpp"
#include <iostream>


void MapGenerator::createPointRec(unsigned int id, float alfa, float alfa_var, int x, int y, unsigned int r, int depth){

    depth++;

    Resources re(200);
    unsigned int _id = id;
    map_point_ptr point = make_shared<MapPoint>(_id, x, y, re);
    map_points_.push_back(point);

    std::cout<<"\n" <<" point" <<_id <<" x " <<x <<" y " <<y;

    float n =2;
    if(depth <=1)
        n=4;
    if(depth<2)
        n=3;
    float a = alfa;
    for(int i =0; i<static_cast<int>(n); i++){
		//sprawdzanie czy galaz grafu osiagnela zadana dlugosc, jezeli tak, funkcja jest przerwana
		if(depth>5){
        depth=0;
        return;
		}
		//dodawanie nowego pkt do polaczen
        unsigned int new_id = this->id;
        this ->id++;
        point->addConnection(new_id);
        
        float new_alfa = alfa+((alfa_var +(static_cast<float>(rand())/RAND_MAX)*alfa_var)*((rand()%2)*(-2)+1))/2;
        //sprawdzanie czy galezie maja dostatecznie duza rozpietosc
        while(abs(a-new_alfa)<0.2)
            new_alfa = alfa+((alfa_var +(static_cast<float>(rand())/RAND_MAX)*alfa_var)*((rand()%2)*(-2)+1))/2;
        a = new_alfa;
        
        if(new_alfa>2*3,14)
            new_alfa-=2*3.14;
        //modyfikacja zmiennych w zaleznosci od polozenia w grafie
        if(depth<=1)
            new_alfa = (alfa+(3.1415/2)*i+new_alfa)/2;
        int _r =(depth>4)? r*1.2 : r;
        int new_x = x + static_cast<int>(sin(new_alfa)*_r);
        int new_y = y - static_cast<int>(cos(new_alfa)*_r);

        float new_alfa_var = alfa_var*0.7;
        createPointRec(new_id, new_alfa, new_alfa_var, new_x, new_y, 0.8*r, depth);

    }
}

vector<map_point_ptr> MapGenerator::generate (){
    srand(time(NULL));
    id = 0;
    point_nr_ = 0;
    r_=200;
    cout<< "TEST";
    unsigned int _id = this->id;
    this->id++;
    createPointRec(_id, 0, 3.1415/2, 700, 700, r_, 0);
    return map_points_;
}
