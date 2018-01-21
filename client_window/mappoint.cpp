#include "mappoint.hpp"

#include <QtWidgets>

using namespace UI;

mapPoint::mapPoint(const QColor &color, int x, int y, int id, unsigned int owner_id, MapView* map_view)
{
    x_ = x;
    y_ = y;
    color_ = color;
    id_ = id;
    owner_id_ = owner_id;
    map_view_=map_view;
    selected_=false;

    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
}

QRectF mapPoint::boundingRect() const
{
    return QRectF(0, 0, RADIUS, RADIUS);
}

QPainterPath mapPoint::shape() const
{
    QPainterPath path;
    path.addEllipse(0, 0, RADIUS, RADIUS);
    return path;
}

void mapPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget);
    QColor fillColor = (option->state & QStyle::State_Selected) ? color_.dark(150) : color_;
    selected_=(option->state & QStyle::State_Selected) ? true : false;
    if(option->state & QStyle::State_Selected){
        map_view_->selected_point_id_= id_;
        map_view_->pointIsSelected();
    }

    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);

    QBrush b = painter->brush();
    painter->setBrush(fillColor);
    painter->drawEllipse(0, 0, RADIUS, RADIUS);
    painter->setBrush(b);
    return;

}

void mapPoint::mousePressEvent(QGraphicsSceneMouseEvent *event){
    map_view_->selected_point_id_= id_;
    QGraphicsItem::mousePressEvent(event);
    update();
}

bool mapPoint::isSelected(){
    return selected_;
}
