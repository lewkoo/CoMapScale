#ifndef GLOBALBUTTON_H
#define GLOBALBUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include "mapmarker.h"


class QGraphicsSceneMouseEvent;
class GeoMap;
class MappingWidget;

class GlobalButton : public QGraphicsRectItem
{
public:
    explicit GlobalButton(GeoMap* map, QString peerID, MappingWidget *parent);

    void setRect(qreal x, qreal y, qreal width, qreal height);
    void setToUndo();
    void setToPeerIcon();

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void zoomButtonPressed();

private:
   bool isPressed (const QPointF &point);

private:
    GeoMap* map;
    MapMarker* peerIcon;
    QGraphicsPixmapItem *icon;
    MappingWidget* parent;
    QString peerID;

    bool buttonPressed;
    bool pressedOverBottomHalf;

};

#endif // GLOBALBUTTON_H
