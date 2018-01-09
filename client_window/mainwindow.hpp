#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include "leftbar.hpp"
#include "rightbar.hpp"
#include "mapview.hpp"
#include "bottombar.hpp"
#include <memory>

typedef std::vector<std::shared_ptr<Ship>> ship_vector;
typedef std::shared_ptr<ship_vector> ship_vector_ptr;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    LeftBar* left_bar_;
    RightBar* right_bar_;
    MapView* map_view_;
    BottomBar* bottom_bar_;
    std::shared_ptr<GameState> game_state_;
    unsigned int player_id_;
public slots:
    void pointSelectionChanged();
    void shipSelectionChanged();
//signals:

};

#endif // MAINWINDOW_HPP
