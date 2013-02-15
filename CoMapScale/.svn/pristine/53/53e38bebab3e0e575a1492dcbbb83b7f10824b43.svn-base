#ifndef CLIENTSTATE_H
#define CLIENTSTATE_H

#include <qgeocoordinate.h>
#include <qgeoboundingbox.h>
#include <QColor>
#include "mapmarker.h"


QTM_USE_NAMESPACE

class PeerState
{
public:
    PeerState(QString id);
    ~PeerState();

    inline void setLastBox(QGeoBoundingBox box) {lastBox = box;}
    inline QGeoBoundingBox getLastBox() {return lastBox;}
    void setLastPosition(QGeoCoordinate coordinate);
    inline QGeoCoordinate getLastPosition() {return lastPosition;}
    inline void setZoomLevel(qreal zoomLevel) {this->zoomLevel = zoomLevel;}
    inline qreal getZoomLevel() {return zoomLevel;}
    inline QString getPeerId() {return peerId;}
    inline void setColour(QColor colour) {this->colour = colour;}
    inline QColor getColour() {return colour; }
    inline void setMarker(MapMarker* peerMarker) {marker = peerMarker;}
    inline MapMarker* getMarker() {return marker;}

    static QColor getColorById(QString clientId);
    static MapMarker::MarkerType getMarkerTypeById(QString clientId);
    static MapMarker::MarkerType getVwMarkerTypeById(QString clientId);

private:
    QGeoCoordinate lastPosition;
    QGeoBoundingBox lastBox;
    qreal zoomLevel;
    QString peerId;
    QColor colour;
    MapMarker* marker;   //Handle to map marker (managed by map object)
};

#endif // CLIENTSTATE_H
