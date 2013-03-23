#ifndef ZOOMSTATUSITEM_H
#define ZOOMSTATUSITEM_H

#include <QSlider>
#include <QWidget>
#include <QGraphicsRectItem>

class QGraphicsSceneMouseEvent;
class GeoMap;

class ZoomStatusItem : public QSlider
{

public:
    explicit ZoomStatusItem(GeoMap* map, QWidget* parent);

    void setPosition(qreal x, qreal y, qreal width, qreal height);
    void setSize(qreal x, qreal y, qreal width, qreal height);
private:
    GeoMap* map;
    QGraphicsRectItem *rect;
};

#endif // ZOOMSTATUSITEM_H
