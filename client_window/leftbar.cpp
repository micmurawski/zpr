#include "leftbar.hpp"
#include <string>

LeftBar::LeftBar(QWidget *parent) {
    order_list_ = new QTextEdit;
    order_list_->setReadOnly(true);
    planet_overwiev_ = new PlanetDetails;
    addTab(order_list_, tr("turn"));
    addTab(planet_overwiev_,  tr("planet"));
    setTabEnabled(1, false);
    connect(planet_overwiev_->ship_list_, SIGNAL(itemSelectionChanged()), this, SIGNAL(selectionChanged()));

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

void LeftBar::loadShips(std::vector<std::shared_ptr<Ship>> ships, bool friendly){
    ships_.clear();
    planet_overwiev_->ship_list_->clear();
    planet_overwiev_->ship_list_->setEnabled(friendly);
    for( auto s : ships){

        if(s){
            int id = s->getId();
            std::string str = "Basic ship id: " + std::to_string(id);
            QString q = QString::fromStdString(str);
            QListWidgetItem* item = new QListWidgetItem(q, planet_overwiev_->ship_list_);
            planet_overwiev_->ship_list_->addItem(item);
            ships_.push_back(s);
            }
    }
}

std::vector<unsigned int> LeftBar::getSelectedShips(const std::shared_ptr<GameState> game_state){
    std::vector<unsigned int> vec;
    QModelIndexList list = planet_overwiev_->ship_list_->selectionModel()->selectedIndexes();
    //iterujemy po liscie zaznaczonych obiektow, pobieramy index i dopisujemy do talbicy odpowiedni wskaznik
    for(auto i : list){
        vec.push_back(ships_[i.row()]->getId());
    }
    return vec;
}

void LeftBar::appendText(std::string text){
    order_list_->append(QString::fromStdString(text));
}

void LeftBar::clearText(){
    order_list_->clear();
}
