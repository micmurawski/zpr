#include "mainwindow.hpp"
#include "mappoint.hpp"
#include "mapview.hpp"
#include <QDockWidget>
#include <QGridLayout>
#include <QSplitter>

//test
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <QDebug>
#include "../game_files/game_engine/game_client.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    wait_for_click_=false;
    ////***********TEST*****************
    player_id_=1;
    GameClient::getInstance();
    std::cout<<"XD";
    for(player_ptr ptr :GameClient::getInstance().gameState_ptr_.get()->players_) std::cout<<ptr.get()->name_<<std::endl;
    game_state_=GameClient::getInstance().gameState_ptr_;
    for(player_ptr ptr :game_state_.get()->players_) std::cout<<ptr.get()->name_<<std::endl;
    //std::cout<<"skopiowano"<<std::endl;
    //std::vector<player_ptr> players;
    //players.push_back(std::make_shared<Player>(std::string("name")));
    //players.push_back(std::make_shared<Player>(std::string("name2")));
    //players.at(0).get()->id_=1;
    //players.at(1).get()->id_=2;
    //game_state_= std::make_shared<GameState>();
    //game_state_.get()->players_=players;
    //game_state_.get()->init();
    //Resources r(500);
    //std::vector<unsigned int> vec;
//
//
    //srand(time(NULL));
    //for(int i = 0; i<=20; i++){
    //int b = rand()%20;
    //vec.push_back(b);
//
//
    //b = rand()%20;
    //vec.push_back(b);
//
    //std::shared_ptr<MapPoint> p = std::make_shared<MapPoint>(i, vec, rand()%500+1, rand()%500+1, r);
    //vec.clear();
    //game_state_->map_points_.push_back(p);
    //}
//
    //game_state_->players_[0]->id_=0;
    //game_state_->players_[1]->resources_.metal_ = 40000;
    //game_state_->players_[1]->id_=1;
    //game_state_->players_[2]->id_=2;
    //game_state_->players_[3]->id_=3;
    //std::shared_ptr<Ship> ship = std::make_shared<Ship>(1,1);
    //game_state_->players_[1]->ships_.push_back(ship);
    //ship = std::make_shared<Ship>(2,2);
    //game_state_->players_[1]->ships_.push_back(ship);
    //ship = std::make_shared<Ship>(3,3);
    //game_state_->players_[2]->ships_.push_back(ship);
    //ship = std::make_shared<Ship>(4,10);
    //game_state_->players_[3]->ships_.push_back(ship);
    //ship = std::make_shared<Ship>(5, 2);
    //game_state_->players_[1]->ships_.push_back(ship);

    map_view_ = new MapView();
    map_view_->readGameStatus(game_state_);
    left_bar_ = new LeftBar;
    right_bar_ = new RightBar;
    bottom_bar_ = new BottomBar;

    QSplitter* h1Splitter = new QSplitter;
    QSplitter* h2Splitter = new QSplitter;

    this->setCentralWidget(map_view_);
    QDockWidget* left_dock = new QDockWidget(this);
    left_dock ->setAllowedAreas(Qt::LeftDockWidgetArea);
    left_dock ->setWidget(left_bar_);
    left_dock ->setTitleBarWidget(new QWidget);
    addDockWidget(Qt::LeftDockWidgetArea, left_dock);

    QDockWidget* right_dock = new QDockWidget(this);
    right_dock ->setAllowedAreas(Qt::RightDockWidgetArea);
    right_dock ->setWidget(right_bar_);
    right_dock ->setTitleBarWidget(new QWidget);
    right_dock ->setMinimumWidth(70);
    addDockWidget(Qt::RightDockWidgetArea, right_dock);

    QDockWidget* bottom_dock = new QDockWidget(this);
    bottom_dock ->setAllowedAreas(Qt::BottomDockWidgetArea);
    bottom_dock ->setWidget(bottom_bar_);
    bottom_dock ->setTitleBarWidget(new QWidget);
    addDockWidget(Qt::BottomDockWidgetArea, bottom_dock);
    connect(map_view_, SIGNAL(selectionChanged()), this, SLOT(pointSelectionChanged()) );
    connect(left_bar_, SIGNAL(selectionChanged()), this, SLOT(shipSelectionChanged()) );

    bottom_bar_->setButtonEnabled(2, false);
    bottom_bar_->setButtonEnabled(3, false);
    bottom_bar_->setButtonEnabled(4, false);

    right_bar_->update(game_state_, 1);

    connect(bottom_bar_, SIGNAL(endTurn()), this, SLOT(endTurn()));
    connect(bottom_bar_, SIGNAL(retakeTurn()), this, SLOT(retakeTurn()));
    connect(bottom_bar_, SIGNAL(createBuilding()), this, SLOT(createBuilding()));
    connect(bottom_bar_, SIGNAL(createShip()), this, SLOT(createShip()));
    connect(bottom_bar_, SIGNAL(moveShip()), this, SLOT(moveShip()));

}

void MainWindow::pointSelectionChanged(){
    if(!(map_view_->pointSelected())){
        //sprawdzamy czy zostala wywolana funkcja moveShip i aplikacja czeka na klikniecie
        if(wait_for_click_){
            //sprawdzamy czy istnieje polaczenie miedzy punktami
            if(game_state_->isConnection(last_point_,static_cast<unsigned int> (map_view_->selected_point_id_) )){
                //tworzymy informacje dla gracza gdzie i jakie statki sa przemieszczane
                std::string s = "move ships:";
                for(auto p : selected_ships_){
                    unsigned int id = p;
                    s = s +" "+ std::to_string(id);
                }
                s= s+ " from " + std::to_string(last_point_) + " to "+std::to_string(map_view_->selected_point_id_)     ;
                left_bar_->appendText(s);
                wait_for_click_=false;
                std::shared_ptr<GameOrder> order = std::make_shared<MoveOrder>(last_point_, static_cast<unsigned int> (map_view_->selected_point_id_), selected_ships_);
                game_orders_.push_back(order);
                return;
            }
        }

        left_bar_->planetNotSelected();
        bottom_bar_->setButtonEnabled(2, false);
        bottom_bar_->setButtonEnabled(3, false);
        bottom_bar_->setButtonEnabled(4, false);

    }
    else{
        auto point = game_state_->getPointById(map_view_->selected_point_id_);
        if(point){
            //sprawdzamy czy na polu stoi budynek
            bool building = false;
            if(game_state_->WhoHasBuilding(map_view_->selected_point_id_)>=0)
                building = true;
            //jezeli nie stoi sprawdzamy czy czy pole jest gracza jezeli tak, mozemy wybudowac budynek -
            //odpowiedni przycisk staje się aktywny, przy okazji ustawiany jest przycisk "create ship"
            if(game_state_->MapPointOwnerId(map_view_->selected_point_id_)==static_cast<int>(player_id_)){
                if(!building)
                    bottom_bar_->setButtonEnabled(3, true);
            bottom_bar_->setButtonEnabled(2, true);
            }
            //przycisk 4 - move ship zostaje odpowiednio ustawiony
            bottom_bar_->setButtonEnabled(4, false);
            //wczytujemy dane do lewego panelu
            left_bar_->loadMapPoint(point, building, game_state_->MapPointOwnerId(map_view_->selected_point_id_));
            //sprawdzamy czy pole nalezy do gracza
            if(game_state_->MapPointOwnerId(map_view_->selected_point_id_) == player_id_)
                left_bar_->loadShips(game_state_->FleetOnPoint(map_view_->selected_point_id_), true);
            else
                left_bar_->loadShips(game_state_->FleetOnPoint(map_view_->selected_point_id_), false);
            left_bar_->planetSelected();
        }
    }

}

void MainWindow::shipSelectionChanged(){
   //jezeli gracz ma jakies zaznaczyl statki, uaktywnia sie przycisk pozwalajacy na wydanie rozkazu przeniesienia statkow
   std::vector<unsigned int> ships =  left_bar_->getSelectedShips(game_state_);
   if(ships.size()){
       bottom_bar_->setButtonEnabled(4, true);
   }else
       bottom_bar_->setButtonEnabled(4, false);
}
void MainWindow::endTurn(){

}
void MainWindow::retakeTurn(){
    game_orders_.clear();
    left_bar_->clearText();

}
void MainWindow::createShip(){
    std::string s = "create ship: p " + std::to_string(map_view_->selected_point_id_);
    left_bar_->appendText(s);
    std::shared_ptr<GameOrder> order = std::make_shared<CreateShipOrder>(static_cast<int>(map_view_->selected_point_id_));
    game_orders_.push_back(order);
}
void MainWindow::createBuilding(){
    //sprawdzanie czy istnieje juz taki rozkaz
    for(auto o: game_orders_){
        if(o->type() == BuildOrder::type_id){
           auto t = std::dynamic_pointer_cast<BuildOrder>(o);
            if(t->getPointId() == map_view_->selected_point_id_ )
                return;
        }
    }
    std::string s = "create building: p" + std::to_string(map_view_->selected_point_id_);
    left_bar_->appendText(s);
    std::shared_ptr<GameOrder> order = std::make_shared<BuildOrder>(static_cast<int>(map_view_->selected_point_id_));
    game_orders_.push_back(order);

}
void MainWindow::moveShip(){
    wait_for_click_=true;
    last_point_=map_view_->selected_point_id_;
    selected_ships_ = left_bar_->getSelectedShips(game_state_);
}
