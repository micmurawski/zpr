#include "planetdetails.hpp"
#include <QGridLayout>

PlanetDetails::PlanetDetails()
{
    QGridLayout* layout = new QGridLayout;

    labels_[0] = new QLabel ;
    properties_[0] = new QLineEdit;
    labels_[0]->setText("planet id");
    properties_[0]->setReadOnly(true);
    labels_[1] = new QLabel ;
    properties_[1] = new QLineEdit;
    labels_[1]->setText("resources");
    properties_[1]->setReadOnly(true);
    labels_[2] = new QLabel ;
    properties_[2] = new QLineEdit;
    labels_[2]->setText("owner");
    properties_[2]->setReadOnly(true);
    labels_[3] = new QLabel ;
    properties_[3] = new QLineEdit;
    labels_[3]->setText("building");
    properties_[3]->setReadOnly(true);

    layout->addWidget(labels_[0], 0, 0);
    layout->addWidget(properties_[0], 0, 1);
    layout->addWidget(labels_[1], 1, 0);
    layout->addWidget(properties_[1], 1, 1);
    layout->addWidget(labels_[2], 2, 0);
    layout->addWidget(properties_[2], 2, 1);
    layout->addWidget(labels_[3], 3, 0);
    layout->addWidget(properties_[3], 3, 1);

    ship_list_ = new QListWidget;
    ship_list_->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ship_list_->setToolTip(tr("You can select multiple ships by using ctrl, shift or dragging mouse over ships"));
    layout->addWidget(ship_list_, 4, 1, 1, 2);
    setLayout(layout);
}

