#ifndef RIGHTBAR_HPP
#define RIGHTBAR_HPP

#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <memory>
#include "../game_files/game_state/game_state.hpp"

/**
 * \class RightBar
 *
 * Klasa interfejsu, Dziedziczy po QFrame, wyświetla atrybuty gracza
 *
 */


class RightBar: public QFrame{
public:
    RightBar();
    void update(std::shared_ptr<GameState> game_state, unsigned int player_id);
    QLabel* name_label_;
    QLineEdit* name_;
    QLabel* metal_label_;
    QLineEdit* metal_;
};

#endif // RIGHTBAR_HPP
