#ifndef ZOOMSLIDERITEM_H
#define ZOOMSLIDERITEM_H

#include <QSlider>
#include <QWidget>
#include <QGraphicsRectItem>

class QGraphicsSceneMouseEvent;
class GeoMap;

class ZoomSliderItem : public QSlider
{
    Q_OBJECT

public:
    explicit ZoomSliderItem(GeoMap* map, QWidget* parent);

    void setPosition(qreal x, qreal y, qreal width, qreal height);
    void setSize(qreal x, qreal y, qreal width, qreal height);
    void mouseReleaseEvent(QMouseEvent *ev);
    void buttonPressed(int value);
    void valueChanged(int value);


signals:
    void sliderPositionChanged();

private:
    GeoMap* map;
    QWidget* parent;
    QGraphicsRectItem *rect;

    //QGraphicsSimpleTextItem *collabScale //change to icon

};

#endif // ZOOMSLIDERITEM_H
