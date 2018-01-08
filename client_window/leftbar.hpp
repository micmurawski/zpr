#ifndef LEFTBAR_HPP
#define LEFTBAR_HPP

#include <QTabWidget>
#include <QTextEdit>
#include <QFrame>
#include <planetdetails.hpp>
#include <memory>
#include "../game_files/game_state/game_state.hpp"

class LeftBar : public QTabWidget {
public:
    LeftBar(QWidget *parent = 0);
private:
    QTextEdit* order_list_;
    PlanetDetails* planet_overwiev_;
    std::vector<std::shared_ptr<Ship>> ships_;
public:
    void planetSelected();
    void planetNotSelected();
    void loadMapPoint(std::shared_ptr<MapPoint> point, bool hasBuilding, int owner_id=-1);
    void loadShips(std::vector<std::shared_ptr<Ship>> ships);

};

#endif // LEFTBAR_HPP
