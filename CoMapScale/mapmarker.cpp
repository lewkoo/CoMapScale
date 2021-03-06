#include "mapmarker.h"
#include "mappingwidget.h"

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
            this->type == MapMarker::HotelType ||
            this->type == MapMarker::UndoType)
    {
        wedge = new Wedge(getWedgeColour());
        setWedgeIcon(type);
        wedge->setWedgeTargetIcon(this);

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

void MapMarker::setMappingWidget(MappingWidget *parent){
    if(parent != NULL && wedge != NULL){
    this->parent = parent;
    wedge->setMappingWidget(parent);
    }
}

void MapMarker::setWedgeIcon(MapMarker::MarkerType type){
    MapMarker* marker = NULL;


    if (type == MapMarker::AnchorType)
    {
        marker = new MapMarker(MapMarker::WedgeAnchorType);
    }
    else if (type == MapMarker::AnchorOrangeType)
    {
         marker = new MapMarker(MapMarker::WedgeAnchorOrangeType);
    }
    else if (type == MapMarker::AnchorPurpleType)
    {
         marker = new MapMarker(MapMarker::WedgeAnchorPurpleType);
    }
    else if (type == MapMarker::AnchorRedType)
    {
         marker = new MapMarker(MapMarker::WedgeAnchorRedType);
    }
    else if (type == MapMarker::AnchorBlueType)
    {
         marker = new MapMarker(MapMarker::WedgeAnchorBlueType);
    }
    else if (type == MapMarker::PeerType)
    {
        marker = new MapMarker(MapMarker::WedgePeerRedType);
    }
    else if (type == MapMarker::PeerOrangeType)
    {
         marker = new MapMarker(MapMarker::WedgePeerOrangeType);
    }
    else if (type == MapMarker::PeerPurpleType)
    {
         marker = new MapMarker(MapMarker::WedgePeerPurpleType);
    }
    else if (type == MapMarker::PeerRedType)
    {
         marker = new MapMarker(MapMarker::WedgePeerRedType);
    }
    else if (type == MapMarker::PeerBlueType)
    {
         marker = new MapMarker(MapMarker::WedgePeerBlueType);
    }
    else if (type == MapMarker::PoiType)
    {
         marker = new MapMarker(MapMarker::WedgePoiType);
    }
    else if (type == MapMarker::UndoType)
    {
         marker = new MapMarker(MapMarker::WedgeUndoType);
    }
    else if (type == MapMarker::HotelType)
    {
        marker = new MapMarker(MapMarker::WedgeHotelType);
    }
    else if (type == MapMarker::RestaurantType)
    {
        marker = new MapMarker(MapMarker::WedgeRestaurantType);
    }

    if(marker != NULL){
    wedge->setWedgeIcon(marker);
    }
}

void MapMarker::setWedge(QPoint screenPos, QRect viewport)
{
    if (wedge != NULL)
    {
        wedge->setWedge(screenPos, viewport);
        setWedgeIcon(this->type);
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
    else if (type == MapMarker::UndoType)
    {
        colour = QColor(123,191,106,255);
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
    case WedgePeerBlueType:
        filename = ":/Icons/wedgePeerBlueFill";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgePeerRedType:
        filename = ":/Icons/wedgePeerRedFill";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgePeerPurpleType:
        filename = ":/Icons/wedgePeerPurpleFill";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgePeerOrangeType:
        filename = ":/Icons/wedgePeerOrangeFill";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgeAnchorRedType:
        filename = ":/Icons/wedgeAnchorRed";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgeAnchorBlueType:
        filename = ":/Icons/wedgeAnchorBlue";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgeAnchorOrangeType:
        filename = ":/Icons/wedgeAnchorOrange";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgeAnchorPurpleType:
        filename = ":/Icons/wedgeAnchorPurple";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgeAnchorType:
        filename = ":/Icons/wedgeAnchor";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgePoiType:
        filename = ":/Icons/wedgePoi";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgeHotelType:
        filename = ":/Icons/wedgeHotel";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgeRestaurantType:
        filename = ":/Icons/wedgeRestaurant";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case UndoType:
        filename = ":/Icons/undoIcon";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case WedgeUndoType:
        filename = ":/Icons/wedgeUndo";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case GlobalButton:
        filename = ":/Icons/globalButton";
        offset = QPoint(-40,-80);
        scale = 40;
        this->setZValue(10);
        break;
    case ScaleIcon:
        filename = ":/Icons/scaleMarkRed";
        offset = QPoint(-40,-80);
        scale = 55;
        this->setZValue(10);
        break;
    case ScaleIconRed:
        filename = ":/Icons/scaleMarkRed";
        offset = QPoint(-40,-80);
        scale = 55;
        this->setZValue(10);
        break;
    case ScaleIconBlue:
        filename = ":/Icons/scaleMarkBlue";
        offset = QPoint(-40,-80);
        scale = 55;
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

QString MapMarker::markerToString(MapMarker::MarkerType type){

    QString filename;

    switch(type){
    case PeerType:
        filename = "PeerType";
        break;
    case PeerOrangeType:
        filename = "PeerOrangeType";
        break;
    case PeerPurpleType:
        filename = "PeerPurpleType";
        break;
    case PeerRedType:
        filename = "PeerRedType";
        break;
    case PeerBlueType:
        filename = "PeerBlueType";
        break;
    case PoiType:
        filename = "PoiType";
        break;
    case AnchorType:
        filename = "AnchorType";
        break;
    case AnchorOrangeType:
        filename = "AnchorOrangeType";
        break;
    case AnchorPurpleType:
        filename = "AnchorPurpleType";
        break;
    case AnchorRedType:
        filename = "AnchorRedType";
        break;
    case AnchorBlueType:
        filename = "AnchorBlueType";
        break;
    case HotelType:
        filename = "HotelType";
        break;
    case RestaurantType:
        filename = "RestaurantType";
        break;
    case WedgePeerBlueType:
        filename = "WedgePeerBlueType";
        break;
    case WedgePeerRedType:
        filename = "WedgePeerRedType";
        break;
    case WedgePeerPurpleType:
        filename = "WedgePeerPurpleType";
        break;
    case WedgePeerOrangeType:
        filename = "WedgePeerOrangeType";
        break;
    case WedgeAnchorRedType:
        filename = "WedgeAnchorRedType";
        break;
    case WedgeAnchorBlueType:
        filename = "WedgeAnchorBlueType";
        break;
    case WedgeAnchorOrangeType:
        filename = "WedgeAnchorOrangeType";
        break;
    case WedgeAnchorPurpleType:
        filename = "WedgeAnchorPurpleType";
        break;
    case WedgeAnchorType:
        filename = "WedgeAnchorType";
        break;
    case WedgePoiType:
        filename = "WedgePoiType";
        break;
    case WedgeHotelType:
        filename = "WedgeHotelType";
        break;
    case WedgeRestaurantType:
        filename = "WedgeRestaurantType";
        break;
    case UndoType:
        filename = "UndoType";
        break;
    case WedgeUndoType:
        filename = "WedgeUndoType";
        break;
    case GlobalButton:
        filename = "GlobalButton";
    case ScaleIconRed:
        filename = "ScaleIcon";
    case ScaleIconBlue:
        filename = "ScaleIcon";
    default:
        filename = "NOT RECOGNIZED";
        break;

    }

    return filename;

}
