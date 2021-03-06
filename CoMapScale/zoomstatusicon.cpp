#include "zoomstatusicon.h"
#include <QGraphicsSceneMouseEvent>
#include "geomap.h"
#include "mapmarker.h"
#include "mappingwidget.h"


zoomstatusicon::zoomstatusicon(GeoMap* map, ZoomSliderItem* slider, QString peerID, MappingWidget* parent ):
    QGraphicsPixmapItem()
{
    this->map = map;
    this->slider = slider;
    this->parent = parent;

    MapMarker::MarkerType type = MapMarker::ScaleIcon;

    if(peerID == "0"){
        type = MapMarker::ScaleIconRed;
    }else if (peerID == "1"){
        type = MapMarker::ScaleIconBlue;
    }else{
        type = MapMarker::ScaleIcon;
    }


    scaleIcon = new MapMarker(type,"");

    scalePressed = false;

    isInteractive = true; //can be pressed by default


    this->setPixmap(scaleIcon->pixmap());
}

void zoomstatusicon::setPeerID(QString peerID){
    MapMarker::MarkerType type = MapMarker::ScaleIcon;

    if(peerID == "0"){
        type = MapMarker::ScaleIconRed;
    }else if (peerID == "1"){
        type = MapMarker::ScaleIconBlue;
    }else{
        type = MapMarker::ScaleIcon;
    }


    scaleIcon = new MapMarker(type,"");

    scalePressed = false;



    this->setPixmap(scaleIcon->pixmap());
    this->setVisible(false);
}

void zoomstatusicon::setRect(qreal x, qreal y, qreal width, qreal height){
    setPos(x,y);
}

bool zoomstatusicon::isPressed(const QPointF &point){
    bool returnValue = false;

    if (this->contains(point) ) //&& point.y() > this->rect().center().y()
    {
        returnValue = true;
    }

    return returnValue;
}

void zoomstatusicon::mousePressEvent(QGraphicsSceneMouseEvent *event){
    const QPointF pos = event->pos();

        if (isPressed(pos) && isInteractive)
        {
            scalePressed = true;
        }

    event->accept();
}

void zoomstatusicon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    const QPointF pos = event->pos();
    if (isPressed(pos) && scalePressed && isInteractive)
    {
        //adjust the scale and locaitons smoothly
        parent->processZoomStatusButtonPress();
        slider->valueChanged(currPosition);

    }
    scalePressed = false;
    event->accept();
}

void zoomstatusicon::setPosition(int newPosition){
    currPosition = newPosition;
    if(parent->sliderStatusEnabled == true){
        setVisible(true);
    }


    switch(newPosition){
    case 18:
        setPos(610,102);
        break;
    case 17:
        setPos(610,111);
        break;
    case 16:
        setPos(610,119);
        break;
    case 15:
        setPos(610,128);
        break;
    case 14:
        setPos(610,136);
        break;
    case 13:
        setPos(610,146);
        break;
    case 12:
        setPos(610,154);
        break;
    case 11:
        setPos(610,163);
        break;
    case 10:
        setPos(610,172);
        break;
    case 9:
        setPos(610,182);
        break;
    case 8:
        setPos(610,191);
        break;
    case 7:
        setPos(610,200);
        break;
    case 6:
        setPos(610,209);
        break;
    case 5:
        setPos(610,218);
        break;
    case 4:
        setPos(610,227);
        break;
    case 3:
        setPos(610,236);
        break;
    case 2:
        setPos(610,244);
        break;
    case 1:
        setPos(610,244);
        break;
    default:
        setVisible(false);


    }


    //updateIconPosition(currPosition); //private method
}

void zoomstatusicon::setInteractivity(bool isEnabled){
    isInteractive = isEnabled;
}
