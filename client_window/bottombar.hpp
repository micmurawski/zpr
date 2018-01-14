#ifndef BOTTOMBAR_HPP
#define BOTTOMBAR_HPP

#include <QFrame>
#include <QPushButton>

class BottomBar : public QFrame{
    Q_OBJECT
public:
    BottomBar();
    void setButtonEnabled(unsigned int index, bool enabled);
signals:
    void endTurn();
    void retakeTurn();
    void createShip();
    void createBuilding();
    void moveShip();
private:
    QPushButton* end_turn_;
    QPushButton* retake_turn_;
    QPushButton* create_ship_;
    QPushButton* create_building_;
    QPushButton* move_ships_;
};

#endif // BOTTOMBAR_HPP
