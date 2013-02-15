#ifndef MAPMARKER_H
#define MAPMARKER_H

//#include <QGeoMapPixmapObject>
#include <qgeomappixmapobject.h>
#include "wedge.h"

QTM_USE_NAMESPACE

class MapMarker : public QGeoMapPixmapObject
{
    //Q_OBJECT
public:
    enum MarkerType
    {
        PeerType,   //Another user
        PeerOrangeType,
        PeerPurpleType,
        PeerRedType,
        PeerBlueType,
        PoiType,    //A point of interest
        AnchorType, //A visit wear
        AnchorOrangeType,
        AnchorPurpleType,
        AnchorRedType,
        AnchorBlueType,
        HotelType,
        RestaurantType
    };

    explicit MapMarker(MapMarker::MarkerType type, QString text = QString(""));
    ~MapMarker();

public:
    inline MapMarker::MarkerType getMarkerType() const { return this->type; }
    inline QString getText() {return text;}
    void setWedge(QPoint screenPos, QRect viewport);
    inline Wedge* getWedge() {return wedge;}

private:
    void setMarkerType (MapMarker::MarkerType type);
    QColor getWedgeColour ();

private:
    MapMarker::MarkerType  type;
    QString text;
    Wedge*   wedge;

};

#endif // MAPMARKER_H
