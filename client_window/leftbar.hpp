#ifndef LEFTBAR_HPP
#define LEFTBAR_HPP

#include <QTabWidget>
#include <QTextEdit>
#include <QFrame>
#include <planetdetails.hpp>

class LeftBar : public QTabWidget {
public:
    LeftBar(QWidget *parent = 0);
private:
    QTextEdit* order_list_;
    PlanetDetails* planet_overwiev_;
public:
    void planetSelected();
    void planetNotSelected();

};

#endif // LEFTBAR_HPP
