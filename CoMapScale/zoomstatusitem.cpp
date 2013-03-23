#include "zoomstatusitem.h"
#include "zoomslideritem.h"
#include "geomap.h"
#include <QGraphicsSceneMouseEvent>
#include <QSlider>

ZoomStatusItem::ZoomStatusItem(GeoMap *map, QWidget* parent):
    QSlider()
{
    this->map = map;

    rect = new QGraphicsRectItem(150,100,50,200); //figure out the background

    setDisabled(true);
    setParent(parent);
    setPageStep(0);
    setTracking(true);
    setOrientation(Qt::Vertical);
    setWindowOpacity(0);
    setTickInterval(1);
    setMaximum(map->maximumZoomLevel());
    setTickPosition(QSlider::TicksRight);
    setContentsMargins(1500,1500,1000,1000);
    setGeometry(150,150,50,200);
    setSliderPosition(map->zoomLevel()); //should pull the other user slider value here
    move(730,100);
    setVisible(true);


}

