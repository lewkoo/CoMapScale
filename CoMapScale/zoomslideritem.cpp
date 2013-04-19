#include "zoomslideritem.h"
#include "geomap.h"
#include "networkclient.h"
#include <QGraphicsSceneMouseEvent>

ZoomSliderItem::ZoomSliderItem(GeoMap *map, QWidget* parent) :
    QSlider()
{
    this->map = map;

    rect = new QGraphicsRectItem(150,100,50,200); //figure out the background

    setParent(parent);
    setPageStep(0);
    setTracking(true);
    setOrientation(Qt::Vertical);
    setWindowOpacity(0);
    setTickInterval(1);
    setMaximum(map->maximumZoomLevel());
    setTickPosition(QSlider::TicksBothSides);
    setContentsMargins(1500,1500,1000,1000);
    setGeometry(150,150,50,170);
    setSliderPosition(map->zoomLevel());
    move(660,120);
    setVisible(true);


}

void ZoomSliderItem::buttonPressed(int value){
    setSliderPosition(value);
    map->setZoomLevel(value);

    emit sliderPositionChanged();
}

void ZoomSliderItem::valueChanged(int value){
    setSliderPosition(value);
    map->setZoomLevel(value);

    emit sliderPositionChanged();
}

void ZoomSliderItem::mouseReleaseEvent(QMouseEvent *ev){
    //int new_map_scale = sliderPosition();
    //map->setZoomLevel(new_map_scale);

    ev->accept();
}

