#include <QPainter>
//#include <QGeoMapPixmapObject>
#include <qgeomappixmapobject.h>
#include <QRect>
#include "mapoverlay.h"
#include "geomap.h"
#include "wedge.h"
#include "global.h"

MapOverlay::MapOverlay(GeoMap* map) :
    QGeoMapOverlay()
{
    this->map = map;
}

void MapOverlay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option)
{
    if (map->isWedgeEnabled())
    {
        QList<QGeoMapObject*> mapObjs = map->mapObjects();
        QList<MapMarker*> paintLast;

        for (int i = 0; i < mapObjs.count(); i++)
        {
            QGeoMapObject* mapObject = mapObjs.at(i);
            MapMarker* pixmapObject = dynamic_cast<MapMarker*>(mapObject);

            if (pixmapObject != NULL )//&& ! viewport().contains(pixmapObject->coordinate()))
            {
                MapMarker::MarkerType type = pixmapObject->getMarkerType();

                if (type == MapMarker::PeerType ||
                    type == MapMarker::PeerBlueType ||
                    type == MapMarker::PeerOrangeType ||
                    type == MapMarker::PeerPurpleType ||
                    type == MapMarker::PeerRedType)
                {
                    paintLast.append(pixmapObject);
                }
                else if (type == MapMarker::AnchorType ||
                        type == MapMarker::AnchorBlueType ||
                        type == MapMarker::AnchorOrangeType ||
                        type == MapMarker::AnchorPurpleType ||
                        type == MapMarker::AnchorRedType)
                {
                    paintLast.prepend(pixmapObject);
                }
                else
                {
                    Wedge* wedge = pixmapObject->getWedge();
                    if (wedge != NULL)
                    {
                        wedge->paint(painter);
                    }
                }
            }
        }

        for (int i = 0; i < paintLast.count(); i++)
        {
            MapMarker* pixmapObject = paintLast.at(i);

            Wedge* wedge = pixmapObject->getWedge();
            if (wedge != NULL)
            {
                wedge->paint(painter);
            }
        }
    }
}
