#ifndef LEFTBAR_HPP
#define LEFTBAR_HPP

#include <QTabWidget>
#include <QTextEdit>
#include <QFrame>
#include <planetdetails.hpp>
#include <memory>
#include <string>
#include "../game_files/game_state/game_state.hpp"

/**
 * \class LeftBar
 *
 * Panel boczny, mający zakładki turn i planet, umożliwiający wyświetlenie atrybutów punktu mapy i przebiegu tury
 *
 */
 
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
    std::vector<unsigned int> getSelectedShips(const std::shared_ptr<GameState> game_state);
    void appendText(std::string text);
    void clearText();

};

#endif // LEFTBAR_HPP
