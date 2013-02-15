#ifndef MAPOVERLAY_H
#define MAPOVERLAY_H

//#include <QGeoMapOverlay>
#include <qgeomapoverlay.h>
#include <QVector>
#include "wedge.h"

using namespace std;
QTM_USE_NAMESPACE

class GeoMap;
class MapMarker;

class MapOverlay : public QGeoMapOverlay
{
public:
    explicit MapOverlay(GeoMap* map);

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option);

//    void setWedge (MapMarker* mapObject);
//    void setWedge (QGeoCoordinate coordinate, QColor colour);
//    void clearWedges (void);
private:
    GeoMap* map;
    //QVector<Wedge> wedges;
};

#endif // MAPOVERLAY_H
