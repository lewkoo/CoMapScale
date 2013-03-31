#ifndef MAPMARKER_H
#define MAPMARKER_H

//#include <QGeoMapPixmapObject>
#include <qgeomappixmapobject.h>
#include "wedge.h"

QTM_USE_NAMESPACE

class Wedge;
class MappingWidget;

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
        RestaurantType,
        WedgePeerBlueType, //A wedge icon
        WedgePeerRedType,
        WedgePeerOrangeType,
        WedgePeerPurpleType,
        WedgeAnchorRedType,
        WedgeAnchorPurpleType,
        WedgeAnchorOrangeType,
        WedgeAnchorBlueType,
        WedgeAnchorType,
        WedgeHotelType,
        WedgeRestaurantType,
        WedgePoiType,
        UndoType,
        WedgeUndoType
    };

    MapMarker(MapMarker::MarkerType type, QString text = QString(""));
    //MapMarker(MapMarker::MarkerType type, QString text = QString(""), MappingWidget *parent = NULL);

    ~MapMarker();

public:
    inline MapMarker::MarkerType getMarkerType() const { return this->type; }
    inline QString getText() {return text;}
    void setWedge(QPoint screenPos, QRect viewport);
    void setMappingWidget(MappingWidget* parent);
    QString markerToString(MapMarker::MarkerType type);
    inline Wedge* getWedge() {return wedge;}

private:
    void setMarkerType (MapMarker::MarkerType type);
    void setWedgeIcon(MapMarker::MarkerType type);
    QColor getWedgeColour ();

private:
    MapMarker::MarkerType  type;
    QString text;
    Wedge*   wedge;
    MappingWidget* parent;
};

#endif // MAPMARKER_H
