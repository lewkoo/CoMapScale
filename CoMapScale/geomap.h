#ifndef GEOMAP_H
#define GEOMAP_H

//#include <QGraphicsGeoMap>
#include <qgraphicsgeomap.h>

#include "mappingwidget.h"

QTM_USE_NAMESPACE

class GeoMap : public QGraphicsGeoMap
{
    Q_OBJECT

public:
    GeoMap (QGeoMappingManager* mapManager, MappingWidget* mapWidget);
    ~GeoMap ();

    void updateWedges(void);
    QPoint coordinateToOffscreenPosition (QGeoCoordinate coordinate);
    void setZoomLevel(qreal zoomLevel); //Shadows parent method.
    void setPixelsPerDegree(void);
    void setWedgeEnabled(bool isEnabled, bool isObjWedgeEnabled);

    inline bool isWedgeEnabled() {return wedgeEnabled;}
    inline bool isObjWedgeEnabled() {return objWedgeEnabled;}

private:
    //Events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *parent);

    void resetWedgePotential();
    void detectWedgeCollisions();

private:
    MappingWidget* mapWidget;
    bool panActive;
    double pixelsPerDegreeLatitude;
    double pixelsPerDegreeLongitude;
    QPen textPen;
    bool wedgeEnabled;      //All Wedges on/off
    bool objWedgeEnabled;   //Wedges for objects (hotel, restaurant, etc.) enabled (only if WedgeEnabled is true).

};

#endif // GEOMAP_H
