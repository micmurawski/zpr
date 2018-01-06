#ifndef MAPVIEW_HPP
#define MAPVIEW_HPP

#include <QGraphicsView>
#include <QFrame>
#include <QLabel>
#include <QSlider>
#include <QToolButton>
#include <QGraphicsScene>

#include "../game_files/game_state/game_state.hpp"
#include <memory>
#include <iostream>
#include <playerscolors.hpp>

class MapView;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(MapView* v) : QGraphicsView(), map_view_(v) {}
private:
    MapView *map_view_;

};

class MapView : public QFrame
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);
    QGraphicsView* graphicsView() const;
    void readGameStatus(std::shared_ptr<GameState> game_state);
    void setSelectedPoint(unsigned int id);
    int getSelectedPoint();

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);

private slots:
    void setupMatrix();
signals:
    void pointSelected();
    void pointDeselected();

private:
    PlayersColors colors_;
    GraphicsView* graphics_view_;
    QGraphicsScene* scene;
    QLabel *label;
    QLabel *label2;
    QSlider *zoomSlider;
    std::shared_ptr<GameState> game_state_;
    int selected_point_;



};


#endif // MAPVIEW_HPP
