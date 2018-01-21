#ifndef PLAYERSCOLORS_HPP
#define PLAYERSCOLORS_HPP

#include <QColor>
#include <vector>

/**
 * \class PlayersColors
 *
 * Klasa odpowiedzialna za przydzielanie koloru graczom
 *
 */


class PlayersColors
{
public:
    PlayersColors();
    QColor getColor(unsigned int id);
private:
    std::vector<QColor> colors_;
};

#endif // PLAYERSCOLORS_HPP
