#ifndef UI_MAPPOINT_HPP
#define UI_MAPPOINT_HPP

#include <QColor>
#include <QGraphicsItem>
#include <mapview.hpp>

/**
 * \class UI:mapPoint
 *
 *  Klasa interfejsu dziedzicząca po QGraphicsItem, będąca graficzną reprezentacją punktu na mapie
 *
 */


namespace UI{
class mapPoint : public QGraphicsItem
{
public:
    enum {RADIUS = 20};
    mapPoint(const QColor &color_, int x_, int y_, int id, unsigned int owner_id, MapView* map_view);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    //bool isVisible(unsigned int id){return true;}
    bool isSelected();
    unsigned int getId(){return id_;}
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){}

private:
    int x_;
    int y_;
    int id_;
    MapView* map_view_;
    QColor color_;
    QVector<QPointF> stuff_;
    unsigned int owner_id_;
    bool selected_;

};

}//namepspace UI
#endif // UI_MAPPOINT_HPP
