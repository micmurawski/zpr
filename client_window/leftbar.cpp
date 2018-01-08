#include "leftbar.hpp"
#include <string>

LeftBar::LeftBar(QWidget *parent) {
    order_list_ = new QTextEdit;
    planet_overwiev_ = new PlanetDetails;
    addTab(order_list_, tr("turn"));
    addTab(planet_overwiev_,  tr("planet"));
    setTabEnabled(1, false);
}

void LeftBar::planetSelected(){
    setTabEnabled(1, true);
    setCurrentIndex(1);
}

void LeftBar::planetNotSelected(){
    setTabEnabled(1, false);
}

void LeftBar::loadMapPoint(std::shared_ptr<MapPoint> point, bool hasBuilding, int owner_id){
    //planet id
    planet_overwiev_->properties_[0]->setText(QString::number(point->getId()));
    //resources
    planet_overwiev_->properties_[1]->setText(QString::number(point->getMetal()));
    //owner id
    QString temp = (owner_id>0)? QString::number(owner_id) : " - ";
    planet_overwiev_->properties_[2]->setText(temp);
    //building
    temp = hasBuilding ? "basic building" : " - ";
    planet_overwiev_->properties_[3]->setText(temp);
}

void LeftBar::loadShips(std::vector<std::shared_ptr<Ship>> ships){
    planet_overwiev_->ship_list_->clear();
    for( auto s : ships){

        if(s){
            int id = s->getId();
            std::string s = "Basic ship id: " + std::to_string(id);
            QString q = QString::fromStdString(s);
            QListWidgetItem* item = new QListWidgetItem(q, planet_overwiev_->ship_list_);
            planet_overwiev_->ship_list_->addItem(item);
            }
    }
}
