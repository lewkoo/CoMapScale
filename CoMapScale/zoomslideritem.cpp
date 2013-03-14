#include "zoomslideritem.h"
#include "geomap.h"
#include <QGraphicsSceneMouseEvent>

ZoomSliderItem::ZoomSliderItem(GeoMap *map, QWidget* parent) :
    QSlider()
{
    connect(this, SIGNAL(sliderReleased()), parent, SLOT(sliderAdjusted()));
    this->map = map;

    rect = new QGraphicsRectItem(150,100,50,200); //figure out the background

    setParent(parent);
    setOrientation(Qt::Vertical);
    setWindowOpacity(0);
    setTickInterval(1);
    setMaximum(map->maximumZoomLevel());
    setTickPosition(QSlider::TicksBothSides);
    setContentsMargins(1500,1500,1000,1000);
    setGeometry(150,150,50,200);
    setSliderPosition(map->zoomLevel());
    move(0,100);
    setVisible(true);


}

void ZoomSliderItem::sliderAdjusted(){
    int new_map_scale = sliderPosition();
    map->setZoomLevel(new_map_scale);

}

void ZoomSliderItem::mouseReleaseEvent(QMouseEvent *ev){
    int new_map_scale = sliderPosition();
    map->setZoomLevel(new_map_scale);

    ev->accept();
}

