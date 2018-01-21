#include "mapview.hpp"
#include <QtWidgets>
#include <qmath.h>
#include "mappoint.hpp"

MapView::MapView (QWidget *parent) : QFrame(parent) {

    graphics_view_ = new GraphicsView(this);
    graphics_view_->setRenderHint(QPainter::Antialiasing, true);
    graphics_view_->setDragMode(QGraphicsView::NoDrag);
    graphics_view_->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphics_view_->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);

    QToolButton *zoomInIcon = new QToolButton;
    zoomInIcon->setText(" + ");
    zoomInIcon->setAutoRepeat(true);
    zoomInIcon->setAutoRepeatInterval(33);
    zoomInIcon->setAutoRepeatDelay(0);
    zoomInIcon->setIconSize(iconSize);
    QToolButton *zoomOutIcon = new QToolButton;
    zoomOutIcon->setText(" - ");
    zoomOutIcon->setAutoRepeat(true);
    zoomOutIcon->setAutoRepeatInterval(33);
    zoomOutIcon->setAutoRepeatDelay(0);
    zoomOutIcon->setIconSize(iconSize);
    zoomSlider = new QSlider;
    zoomSlider->setOrientation(Qt::Horizontal);
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::NoTicks);
    
    QHBoxLayout *zoomSliderLayout = new QHBoxLayout;
    zoomSliderLayout->addWidget(zoomOutIcon);
    zoomSliderLayout->addWidget(zoomSlider);
    zoomSliderLayout->addWidget(zoomInIcon);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(graphics_view_, 0, 0);
    topLayout->addLayout(zoomSliderLayout, 1, 0);
    setLayout(topLayout);

    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(zoomOutIcon, SIGNAL(clicked()), this, SLOT(zoomOut()));
    connect(zoomInIcon, SIGNAL(clicked()), this, SLOT(zoomIn()));

    setupMatrix();
    point_selected_=false;
    selected_point_id_=-1;
}


QGraphicsView* MapView::graphicsView() const {
    return static_cast<QGraphicsView*> (graphics_view_);
}

void MapView::setupMatrix(){
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

    QMatrix matrix;
    matrix.scale(scale, scale);

    graphics_view_->setMatrix(matrix);
}

void MapView::zoomIn(int level){
    zoomSlider->setValue(zoomSlider->value() + level);
}

void MapView::zoomOut(int level){
    zoomSlider->setValue(zoomSlider->value() - level);
}

void MapView::readGameStatus(std::shared_ptr<GameState> game_state){
    game_state_ = game_state;

    scene = new QGraphicsScene;
    graphicsView()->setScene(scene);

    connect(scene, SIGNAL(selectionChanged()), this, SLOT(selectionChangedSlot()));

    graphicsView()->setBackgroundBrush(QBrush(QColor::fromRgb(40, 40, 40), Qt::SolidPattern));


    //drawing planets
    for( auto map_point : game_state->map_points_){

        //dodwanianie planet do scene
        //zależnie od przynależności nadawany jest kolor
        QColor color;
        int player_id = game_state->MapPointOwnerId(map_point->getId());
        if(player_id<0)
            color = Qt::gray;
        else
            color = colors_.getColor(static_cast<unsigned int>(player_id));
        //tworzenie planety
        QGraphicsItem *item = new UI::mapPoint(color, 0, 0, map_point->getId(),player_id, this);
        item->setPos(QPointF(map_point->getX(),map_point->getY()));
        item->setZValue(3);
        scene->addItem(item);

        //dodawanie połączeń
        for( auto connection : map_point->getConnections()){
            if(game_state->getPointById(connection)==nullptr)
                continue;
            int x1 = map_point->getX()+UI::mapPoint::RADIUS/2;
            int x2 = (game_state->getPointById(connection))->getX()+UI::mapPoint::RADIUS/2;
            int y1 = map_point->getY()+UI::mapPoint::RADIUS/2;
            int y2 = (game_state->getPointById(connection))->getY()+UI::mapPoint::RADIUS/2;

            QGraphicsLineItem* line  = new QGraphicsLineItem (x1, y1, x2, y2);
            QPen pen;
            pen.setWidth(2);
            pen.setColor(QColor(150,240 , 240));
            line->setPen(pen);
            item = line;
            item->setZValue(2);
            scene->addItem(item);
        }
       //rysowanie oznaczenia, że na punkcie znajduje się flota gracza
       player_id = game_state->WhoHasFleet(map_point->getId());
       if(player_id>=0){
        color = colors_.getColor(player_id);
        QGraphicsRectItem* rect = new QGraphicsRectItem(map_point->getX(), map_point->getY()-12, 20, 7);
        rect->setBrush(QBrush(color));
        item = rect;
        item->setZValue(3);
        scene->addItem(item);
        }//for
    }//for

}//readGameStatus



void MapView::selectionChangedSlot(){
    point_selected_=false;
    emit selectionChanged();
}

void MapView::pointIsSelected(){
   if(!point_selected_){
       point_selected_=true;
        emit selectionChanged();
        }
}

