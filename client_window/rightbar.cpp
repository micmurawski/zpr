#include "rightbar.hpp"
#include <QVBoxLayout>

RightBar::RightBar()
{
    name_label_ = new QLabel(tr("name"));
    name_ = new QLineEdit;
    name_->setReadOnly(true);
    metal_label_ = new QLabel(tr("metal"));
    metal_ = new QLineEdit;
    metal_->setReadOnly(true);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSpacing(5);
    layout->setContentsMargins(5,20,5,(this->size()).height());
    layout->addWidget(name_label_, 0, Qt::AlignTop);
    layout->addWidget(name_,0,  Qt::AlignTop);
    layout->addWidget(metal_label_, 0, Qt::AlignTop);
    layout->addWidget(metal_,0,  Qt::AlignTop);


    setLayout(layout);
}

void RightBar::update(std::shared_ptr<GameState> game_state, unsigned int player_id){
    QString s;
    s = QString::number(game_state->players_[player_id]->resources_.metal_);
    metal_->setText(s);
}
