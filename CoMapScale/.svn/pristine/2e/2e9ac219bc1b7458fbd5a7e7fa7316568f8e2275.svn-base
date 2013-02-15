#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
//#include <QGeoMapPixmapObject>
#include <qgeomappixmapobject.h>
//#include <QGeoBoundingBox>
#include <qgeoboundingbox.h>
#include <QPainter>
#include <QPen>
#include "geomap.h"
#include "mapoverlay.h"

GeoMap::GeoMap (QGeoMappingManager* mapManager, MappingWidget* mapWidget) :
    QGraphicsGeoMap(mapManager), mapWidget (mapWidget)
{
    panActive = false;
    wedgeEnabled = true;
    objWedgeEnabled = false;
    textPen.setColor(QColor("black"));
}

GeoMap::~GeoMap()
{

}

void GeoMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    panActive = true;
    event->accept();
}

void GeoMap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    panActive = false;
    event->accept();
}

void GeoMap::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (panActive)
    {
        QPointF delta = event->lastPos() - event->pos();
        pan(delta.x(), delta.y());
    }

    mapWidget->mapPositionChanged();
    event->accept();
}

void GeoMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *parent)
{
    QList<QGeoMapObject*> mapObjects;
    MapMarker* pixmapObject = NULL;
    QGeoCoordinate coordinate;

    QGraphicsGeoMap::paint(painter, option, parent);
    painter->setPen(this->textPen);
    QPointF offset(-20, 35);

    mapObjects = this->mapObjects();

    for (int i = 0; i < mapObjects.count(); i++)
    {
        QGeoMapObject* mapObject = mapObjects.at(i);
        pixmapObject = dynamic_cast<MapMarker*>(mapObject);

        if (pixmapObject != NULL)
        {
            coordinate = pixmapObject->coordinate();

            if (!pixmapObject->getText().isEmpty() && viewport().contains(pixmapObject->coordinate()))
            {
                QPointF position = this->coordinateToScreenPosition(coordinate) + offset;
                painter->drawText(position, pixmapObject->getText());
            }
        }
    }
}

void GeoMap::updateWedges()
{
    if (wedgeEnabled)
    {
        MapMarker* pixmapObject = NULL;

        resetWedgePotential();
        detectWedgeCollisions();

        QList<QGeoMapObject*> mapObjs = mapObjects();

        for (int i = 0; i < mapObjs.count(); i++)
        {
            QGeoMapObject* mapObject = mapObjs.at(i);
            pixmapObject = dynamic_cast<MapMarker*>(mapObject);

            if (pixmapObject != NULL)
            {                
                MapMarker::MarkerType markerType = pixmapObject->getMarkerType();

                //Only add wedges for objects if objWedge is enabled
                if (objWedgeEnabled || !(markerType == MapMarker::RestaurantType || markerType == MapMarker::HotelType))
                {

                    Wedge* wedge = pixmapObject->getWedge();

                    if (wedge != NULL)
                    {
                        wedge->updatePotential();
                    }

                    QPoint screenPos = this->coordinateToOffscreenPosition(pixmapObject->coordinate());
                    QRect viewport = QRect(0, 0, this->size().width(), this->size().height());
                    pixmapObject->setWedge(screenPos, viewport);
                }
            }
        }
    }
}

void GeoMap::resetWedgePotential()
{
    MapMarker* pixmapObject = NULL;
    QList<QGeoMapObject*> mapObjs = mapObjects();

    for (int i = 0; i < mapObjs.count(); i++)
    {
        QGeoMapObject* mapObject = mapObjs.at(i);
        pixmapObject = dynamic_cast<MapMarker*>(mapObject);

        if (pixmapObject != NULL )
        {
            Wedge* wedge = pixmapObject->getWedge();
            if (wedge != NULL)
            {
                wedge->resetPotentialDelta();
            }
        }
    }
}

void GeoMap::detectWedgeCollisions()
{
    MapMarker* pixmapObject = NULL;
    QList<QGeoMapObject*> mapObjs = mapObjects();

    //Adjust for wedge collisions. O(n^2)
    for (int i = 0; i < mapObjs.count(); i++)
    {
        QGeoMapObject* mapObject = mapObjs.at(i);
        pixmapObject = dynamic_cast<MapMarker*>(mapObject);

        if (pixmapObject != NULL && !this->viewport().contains(pixmapObject->coordinate()))
        {
            //Only do check for objects if objWedge is enabled
            MapMarker::MarkerType thisMarkerType = pixmapObject->getMarkerType();
            if (objWedgeEnabled || !(thisMarkerType == MapMarker::RestaurantType || thisMarkerType == MapMarker::HotelType))
            {
                Wedge* thisWedge = pixmapObject->getWedge();

                if (thisWedge != NULL)
                {
                    for (int j = 0; j < mapObjs.count(); j++)
                    {
                        if (i != j)
                        {
                            QGeoMapObject* otherMapObject = mapObjs.at(j);
                            MapMarker* otherPixmapObject = dynamic_cast<MapMarker*>(otherMapObject);

                            if (otherPixmapObject != NULL && !this->viewport().contains(otherPixmapObject->coordinate()))
                            {
                                //Only do check for objects if objWedge is enabled
                                MapMarker::MarkerType otherMarkerType = otherPixmapObject->getMarkerType();
                                if (objWedgeEnabled || !(otherMarkerType == MapMarker::RestaurantType || otherMarkerType == MapMarker::HotelType))
                                {
                                    Wedge* otherWedge = otherPixmapObject->getWedge();

                                    thisWedge->detectCollision(otherWedge);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

QPoint GeoMap::coordinateToOffscreenPosition (QGeoCoordinate coordinate)
{
    QPoint pixelPosition;
    QGeoCoordinate originCoordinate = screenPositionToCoordinate(QPointF(0,0));
    QGeoCoordinate differenceFromOrigin = QGeoCoordinate (originCoordinate.latitude() - coordinate.latitude(), coordinate.longitude() - originCoordinate.longitude());

    pixelPosition = QPoint(differenceFromOrigin.longitude() * pixelsPerDegreeLongitude, differenceFromOrigin.latitude() * pixelsPerDegreeLatitude);

    return pixelPosition;
}

void GeoMap::setZoomLevel(qreal zoomLevel)
{
    QGraphicsGeoMap::setZoomLevel(zoomLevel);

    setPixelsPerDegree();

    mapWidget->mapPositionChanged();
}

void GeoMap::setPixelsPerDegree()
{
    QGeoCoordinate topLeft, topRight, bottomLeft;
    double screenWidthDegrees;
    double screenHeightDegrees;

    topLeft = viewport().topLeft();
    topRight = viewport().topRight();
    bottomLeft = viewport().bottomLeft();

    QPointF botRight = coordinateToScreenPosition(viewport().bottomRight());

    screenWidthDegrees = topRight.longitude() - topLeft.longitude();
    screenHeightDegrees = topLeft.latitude() - bottomLeft.latitude();

    pixelsPerDegreeLongitude = this->size().width() / screenWidthDegrees;
    pixelsPerDegreeLatitude = this->size().height() / screenHeightDegrees;
}

void GeoMap::setWedgeEnabled(bool isEnabled, bool objWedgeEnabled)
{
    this->wedgeEnabled = isEnabled;
    this->objWedgeEnabled = objWedgeEnabled;
}
