#include "playerscolors.hpp"
#include <iostream>

PlayersColors::PlayersColors()
{
    colors_.push_back(Qt::red);
    colors_.push_back(Qt::green);
    colors_.push_back(Qt::blue);
    colors_.push_back(QColor(255,115,0)); //orange
    colors_.push_back(QColor(221,255,0)); //yellow
    colors_.push_back(QColor(234, 0, 255));//pink
    colors_.push_back(QColor(170, 0, 255));//purple
    colors_.push_back(QColor(0, 240, 255));//cyan
 }

QColor PlayersColors::getColor(unsigned int id){
    std::cerr<<"id"<<id;
    if(id<colors_.size())
        return colors_[id];
    else
        return Qt::black;
}
