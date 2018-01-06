#include "leftbar.hpp"

LeftBar::LeftBar(QWidget *parent) {
    order_list_ = new QTextEdit;
    planet_overwiev_ = new PlanetDetails;
    addTab(order_list_, tr("turn"));
    addTab(planet_overwiev_,  tr("planet"));
    setTabEnabled(1, false);
}

void LeftBar::planetSelected(){
    setTabEnabled(1, true);
    setCurrentIndex(1);
}

void LeftBar::planetNotSelected(){
    setTabEnabled(1, false);
}
