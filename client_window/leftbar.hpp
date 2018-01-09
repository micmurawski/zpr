#ifndef LEFTBAR_HPP
#define LEFTBAR_HPP

#include <QTabWidget>
#include <QTextEdit>
#include <QFrame>
#include <planetdetails.hpp>
#include <memory>
#include "../game_files/game_state/game_state.hpp"

typedef std::vector<std::shared_ptr<Ship>> ship_vector;
typedef std::shared_ptr<ship_vector> ship_vector_ptr;

class LeftBar : public QTabWidget {
    Q_OBJECT
signals:
    void selectionChanged();
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
    void loadShips(std::vector<std::shared_ptr<Ship>> ships, bool friendly);
    ship_vector getSelectedShips(const std::shared_ptr<GameState> game_state);

};

#endif // LEFTBAR_HPP
