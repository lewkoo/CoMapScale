#include "mapmarker.h"

MapMarker::MapMarker(MapMarker::MarkerType type, QString text)
{
    setMarkerType (type);
    this->text = text;

    if (this->type == MapMarker::AnchorType ||
            this->type == MapMarker::AnchorOrangeType ||
            this->type == MapMarker::AnchorPurpleType ||
            this->type == MapMarker::AnchorRedType ||
            this->type == MapMarker::AnchorBlueType ||
            this->type == MapMarker::PeerType ||
            this->type == MapMarker::PeerOrangeType ||
            this->type == MapMarker::PeerPurpleType ||
            this->type == MapMarker::PeerRedType ||
            this->type == MapMarker::PeerBlueType ||
            this->type == MapMarker::PoiType ||
            this->type == MapMarker::RestaurantType ||
            this->type == MapMarker::HotelType)
    {
        wedge = new Wedge(getWedgeColour());
    }
    else
    {
        wedge = NULL;
    }
}

MapMarker::~MapMarker()
{
    if (wedge != NULL)
    {
        delete wedge;
    }
}

void MapMarker::setWedge(QPoint screenPos, QRect viewport)
{
    if (wedge != NULL)
    {
        wedge->setWedge(screenPos, viewport);
    }
}

QColor MapMarker::getWedgeColour()
{
    QColor colour;

    if (type == MapMarker::AnchorType)
    {
        colour = QColor(Qt::blue);
    }
    else if (type == MapMarker::AnchorOrangeType)
    {
        colour = QColor("orange");
    }
    else if (type == MapMarker::AnchorPurpleType)
    {
        colour = QColor("violet");
    }
    else if (type == MapMarker::AnchorRedType)
    {
        colour = QColor("hotpink");
    }
    else if (type == MapMarker::AnchorBlueType)
    {
        colour = QColor("skyblue");
    }
    else if (type == MapMarker::PeerType)
    {
        colour = QColor(Qt::red);
    }
    else if (type == MapMarker::PeerOrangeType)
    {
        colour = QColor("darkorange");
    }
    else if (type == MapMarker::PeerPurpleType)
    {
        colour = QColor("purple");
    }
    else if (type == MapMarker::PeerRedType)
    {
        colour = QColor("red");
    }
    else if (type == MapMarker::PeerBlueType)
    {
        colour = QColor("blue");
    }
    else if (type == MapMarker::PoiType)
    {
        colour = QColor(Qt::yellow);
    }
//    else if (type == MapMarker::HotelType)
//    {
//        colour = QColor("green");
//    }
//    else if (type == MapMarker::RestaurantType)
//    {
//        colour = QColor("cyan");
//    }
    else
    {
        colour = QColor(Qt::black);
    }

    return colour;
}

void MapMarker::setMarkerType (MapMarker::MarkerType type)
{
    QString filename;
    QPoint offset;
    int scale;

    this->type = type;

    switch (this->type)
    {
    case PeerType:
        filename = ":/Icons/peer";
        offset = QPoint (-23, -14);
        scale = 40;
        break;
    case PeerOrangeType:
        filename = ":/Icons/peerOrange";
        offset = QPoint (-23, -14);
        scale = 40;
        this->setZValue(20);
        break;
    case PeerPurpleType:
        filename = ":/Icons/peerPurple";
        offset = QPoint (-23, -14);
        scale = 40;
        this->setZValue(20);
        break;
    case PeerRedType:
        filename = ":/Icons/peerRed";
        offset = QPoint (-23, -14);
        scale = 40;
        this->setZValue(20);
        break;
    case PeerBlueType:
        filename = ":/Icons/peerBlue";
        offset = QPoint (-23, -14);
        scale = 40;
        this->setZValue(20);
        break;
    case PoiType:
        filename = ":/Icons/poi";
        offset = QPoint (-23, -22);
        scale = 40;
        break;
    case AnchorType:
        filename = ":/Icons/anchor";
        offset = QPoint (-20, -25);
        scale = 40;
        break;
    case AnchorOrangeType:
        filename = ":/Icons/anchorOrange";
        offset = QPoint (-20, -25);
        scale = 40;
        break;
    case AnchorPurpleType:
        filename = ":/Icons/anchorPurple";
        offset = QPoint (-20, -25);
        scale = 40;
        break;
    case AnchorRedType:
        filename = ":/Icons/anchorRed";
        offset = QPoint (-20, -25);
        scale = 40;
        break;
    case AnchorBlueType:
        filename = ":/Icons/anchorBlue";
        offset = QPoint (-20, -25);
        scale = 40;
        break;
    case HotelType:
        filename = ":/Icons/hotel";
        offset = QPoint (-46, -24);
        scale = 40;
        this->setZValue(10);
        break;
    case RestaurantType:
        filename = ":/Icons/restaurant";
        offset = QPoint (-38, -27);
        scale = 40;
        this->setZValue(10);
        break;
    }

    //Correct the offset
    float scaleRatio = ((float)-scale) / (2 * offset.x());
    offset.setX(offset.x() * scaleRatio);
    offset.setY(offset.y() * scaleRatio);

    setOffset (offset);
    QPixmap pixmap = QPixmap(filename).scaledToWidth(scale, Qt::SmoothTransformation);
    setPixmap (pixmap);
}
