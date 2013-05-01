#ifndef ZOOMSTATUSICON_H
#define ZOOMSTATUSICON_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include "mapmarker.h"

class ZoomButtonItemPimpl;
class QGraphicsSceneMouseEvent;
class GeoMap;
class ZoomSliderItem;
class MappingWidget;

class zoomstatusicon : public QGraphicsPixmapItem
{
public:
    explicit zoomstatusicon(GeoMap* map, ZoomSliderItem* slider, QString peerID, MappingWidget* parent);
    void setRect(qreal x, qreal y, qreal width, qreal height);
    void setPeerID(QString peerID);

    void setPosition(int newPosition);
    void setInteractivity(bool isEnabled);
    //void setType(QString peerID);

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

private:
    bool isPressed (const QPointF &point);

private:
    GeoMap* map;
    MappingWidget* parent;
    MapMarker* scaleIcon;
    ZoomSliderItem* slider;
    QString peerID;

    int currPosition; //current position equal to the peer's slider

    QGraphicsSimpleTextItem *plusText;
    QGraphicsSimpleTextItem *minusText;

    bool scalePressed;
    bool isInteractive;
};


#endif // ZOOMSTATUSICON_H
