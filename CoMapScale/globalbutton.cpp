#include "globalbutton.h"
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include "geomap.h"
#include "mapmarker.h"
#include "mappingwidget.h"

GlobalButton::GlobalButton(GeoMap* map, QString peerID, MappingWidget *parent) :
    QGraphicsRectItem()
{
    this->map = map;
    this->parent = parent;
    this->peerID = peerID;

    //set peer icon based on peer ID

    qDebug()<< "Peer ID: " + peerID;

    if(peerID == "0"){
        MapMarker::MarkerType type = MapMarker::GlobalButton;
        peerIcon = new MapMarker(type, "");
    }else if (peerID == "1"){
        MapMarker::MarkerType type = MapMarker::GlobalButton;
        peerIcon = new MapMarker(type, "");
    }

    buttonPressed = false;





    //draw icon

    icon = new QGraphicsPixmapItem(peerIcon->pixmap(), this);


}

void GlobalButton::setRect(qreal x, qreal y, qreal width, qreal height){
    QGraphicsRectItem::setRect(x, y, width, height);
    setPen(QPen(QBrush(), -10));
    setBrush(QBrush(QColor(0,0,0,0)));

    icon->setPos(x+5,y);
    icon->setVisible(true);
}

bool GlobalButton::isPressed(const QPointF &point){
    bool returnValue = false;

    if (this->contains(point) ) //&& point.y() > this->rect().center().y()
    {
        returnValue = true;
    }

    return returnValue;
}

void GlobalButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    const QPointF pos = event->pos();

        if (isPressed(pos))
        {
            buttonPressed = true;
        }

    event->accept();
}


void GlobalButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    const QPointF pos = event->pos();
    if (isPressed(pos) && buttonPressed)
    {
        //adjust the scale and locaitons smoothly
        parent->processGlobalButtonIconPress();

    }
    buttonPressed = false;
    event->accept();
}

void GlobalButton::setToUndo(){
    MapMarker::MarkerType type = MapMarker::WedgeUndoType;
    peerIcon = new MapMarker(type, "");
    icon->setPixmap(peerIcon->pixmap());
}

void GlobalButton::setToPeerIcon(){

    if(this->peerID == "0"){
        MapMarker::MarkerType type = MapMarker::GlobalButton;
        peerIcon = new MapMarker(type, "");
    }else if (this->peerID == "1"){
        MapMarker::MarkerType type = MapMarker::GlobalButton;
        peerIcon = new MapMarker(type, "");
    }

    icon->setPixmap(peerIcon->pixmap());
}

