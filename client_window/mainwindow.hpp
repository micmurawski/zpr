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
public slots:
    void selectionChanged();
//signals:

};

#endif // MAINWINDOW_HPP
