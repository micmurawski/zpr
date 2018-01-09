#include "bottombar.hpp"
#include <QHBoxLayout>

BottomBar::BottomBar()
{
    end_turn_ = new QPushButton("end\nturn");
    retake_turn_  = new QPushButton("retake\nturn");
    create_ship_  = new QPushButton("create\nship");
    create_building_  = new QPushButton("create\nbuilding");
    move_ships_  = new QPushButton("move\nship");
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(end_turn_);
    layout->addWidget(retake_turn_);
    layout->addWidget(create_ship_);
    layout->addWidget(create_building_);
    layout->addWidget(move_ships_);
    setLayout(layout);


}

void BottomBar::setButtonEnabled(unsigned int index, bool enabled){
    switch(index){
    case 0:
        end_turn_->setEnabled(enabled);
    break;
    case 1:
        retake_turn_->setEnabled(enabled);
    break;
    case 2:
        create_ship_->setEnabled(enabled);
    break;
    case 3:
        create_building_->setEnabled(enabled);
    break;
    case 4:
        move_ships_->setEnabled(enabled);
    break;
    }
}

