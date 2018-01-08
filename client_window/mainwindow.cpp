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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    game_state_= std::make_shared<GameState>(4);
    Resources r(500);
    std::vector<unsigned int> vec;

    //***********TEST*****************
    srand(time(NULL));
    for(int i = 0; i<=20; i++){
    int b = rand()%20;
    vec.push_back(b);


    b = rand()%20;
    vec.push_back(b);

    std::shared_ptr<MapPoint> p = std::make_shared<MapPoint>(i, vec, rand()%500+1, rand()%500+1, r);
    vec.clear();
    game_state_->map_points_.push_back(p);
    }

    game_state_->players_[0]->id_=0;
    game_state_->players_[1]->id_=1;
    game_state_->players_[2]->id_=2;
    game_state_->players_[3]->id_=3;
    std::shared_ptr<Ship> ship = std::make_shared<Ship>(1,1);
    game_state_->players_[1]->ships_.push_back(ship);
    ship = std::make_shared<Ship>(2,2);
    game_state_->players_[1]->ships_.push_back(ship);
    ship = std::make_shared<Ship>(3,3);
    game_state_->players_[2]->ships_.push_back(ship);
    ship = std::make_shared<Ship>(10,10);
    game_state_->players_[3]->ships_.push_back(ship);

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
    connect(map_view_, SIGNAL(selectionChanged()), this, SLOT(selectionChanged()) );

}

void MainWindow::selectionChanged(){
    if(!(map_view_->pointSelected())){
        left_bar_->planetNotSelected();

    }
    else{
        auto point = game_state_->getPointById(map_view_->selected_point_id_);
        if(point){
            left_bar_->loadMapPoint(point, true, game_state_->MapPointOwnerId(map_view_->selected_point_id_));
            left_bar_->loadShips(game_state_->FleetOnPoint(map_view_->selected_point_id_));
            left_bar_->planetSelected();
        }
    }

}

