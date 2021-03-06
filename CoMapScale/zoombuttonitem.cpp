#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include "zoombuttonitem.h"
#include "geomap.h"
#include "zoomslideritem.h"

QTM_USE_NAMESPACE

ZoomButtonItem::ZoomButtonItem(GeoMap* map, ZoomSliderItem* slider) :
    QGraphicsRectItem()
{
    this->map = map;
    this->slider = slider;
    pressedOverTopHalf = false;
    pressedOverBottomHalf = false;

    setPen(QPen(QBrush(), 0));
    setBrush(QBrush(QColor(0,0,0,150)));

    plusText = new QGraphicsSimpleTextItem(this);
    plusText->setText("+");
    plusText->setBrush(QBrush(Qt::white));

    minusText = new QGraphicsSimpleTextItem(this);
    minusText->setText("-");
    minusText->setBrush(QBrush(Qt::white));
}

void ZoomButtonItem::setRect(qreal x, qreal y, qreal width, qreal height)
{
    QGraphicsRectItem::setRect(x, y, width, height);

    QFont font;
    font.setFixedPitch(true);
    font.setPixelSize(height/9.0);
    plusText->setFont(font);
    minusText->setFont(font);

    QRectF plusBound = plusText->boundingRect();
    QPointF plusCenter(x+width/2.0, y+height/12.0);
    QPointF plusDelta = plusCenter - plusBound.center();
    plusText->setPos(plusDelta);

    QRectF minusBound = minusText->boundingRect();
    QPointF minusCenter(x+width/2.0, y+9.0*height/10.0);
    QPointF minusDelta = minusCenter - minusBound.center();
    minusText->setPos(minusDelta);
}

bool ZoomButtonItem::isTopHalf (const QPointF &point)
{
    bool returnValue = false;

    if (this->contains(point) && point.y() <= this->rect().center().y())
    {
        returnValue = true;
    }

    return returnValue;
}

bool ZoomButtonItem::isBottomHalf (const QPointF &point)
{
    bool returnValue = false;

    if (this->contains(point) && point.y() > this->rect().center().y())
    {
        returnValue = true;
    }

    return returnValue;
}

void ZoomButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    const QPointF pos = event->pos();
    if (!pressedOverTopHalf && !pressedOverBottomHalf)
    {
        if (isTopHalf(pos))
        {
            pressedOverTopHalf = true;
        }
        else if (isBottomHalf(pos))
        {
            pressedOverBottomHalf = true;
        }
    }
    event->accept();
}

void ZoomButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    const QPointF pos = event->pos();
    if (isTopHalf(pos) && pressedOverTopHalf)
    {
        //map->setZoomLevel(map->zoomLevel() + 1.0);
        slider->buttonPressed(map->zoomLevel()+1.0);

    }
    else if (isBottomHalf(pos) && pressedOverBottomHalf)
    {
        //adjust the slider position
        slider->buttonPressed(map->zoomLevel()-1.0);
        //map->setZoomLevel(map->zoomLevel() - 1.0);
    }
    pressedOverBottomHalf = false;
    pressedOverTopHalf = false;
    event->accept();
}
