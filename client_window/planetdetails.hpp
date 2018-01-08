#ifndef PLANETDETAILS_HPP
#define PLANETDETAILS_HPP

#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <memory>
#include <QListWidget>
#include "../game_files/game_state/game_state.hpp"

class PlanetDetails : public QFrame {
public:
    PlanetDetails();
    QLabel* labels_[4];
    QLineEdit* properties_[4];
    QListWidget* ship_list_;
};

#endif // PLANETDETAILS_HPP
