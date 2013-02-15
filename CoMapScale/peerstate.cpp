#include "peerstate.h"
#include "mapmarker.h"

PeerState::PeerState(QString id)
{
    this->peerId = id;
    lastPosition = QGeoCoordinate(-27.5769, 153.1);
    lastBox = QGeoBoundingBox(lastPosition, 4, 2);
    setColour(PeerState::getColorById(id));
    zoomLevel = 15;
}

PeerState::~PeerState()
{
}

void PeerState::setLastPosition(QGeoCoordinate coordinate)
{
    lastPosition = coordinate;
    marker->setCoordinate(coordinate);
}

//Static method
QColor PeerState::getColorById(QString clientId)
{
    //Assume id is an integer.
    int id = clientId.toInt();
    QColor colour;

    switch (id)
    {
    case 0:
        colour = QColor("orange");
        break;
    case 1:
        colour = QColor("purple");
        break;
    default:
        colour = QColor("red");
    }

    return colour;
}

//Static method
MapMarker::MarkerType PeerState::getMarkerTypeById(QString clientId)
{
    //Assume id is an integer.
    int id = clientId.toInt();
    MapMarker::MarkerType markerType;

    switch (id)
    {
    case 0:
        markerType = MapMarker::PeerRedType;
        break;
    case 1:
        markerType = MapMarker::PeerBlueType;
        break;
    default:

        markerType = MapMarker::PeerType;
    }

    return markerType;
}

MapMarker::MarkerType PeerState::getVwMarkerTypeById(QString clientId)
{
    //Assume id is an integer.
    int id = clientId.toInt();
    MapMarker::MarkerType markerType;

    switch (id)
    {
    case 0:
        markerType = MapMarker::AnchorRedType;
        break;
    case 1:
        markerType = MapMarker::AnchorBlueType;
        break;
    default:

        markerType = MapMarker::AnchorType;
    }

    return markerType;
}
