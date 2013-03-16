#include "wedgeicon.h"
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>



WedgeIcon::WedgeIcon() :
    QGraphicsRectItem()
{
    iconPressed = false;
}

bool WedgeIcon::isIconPressed (const QPointF &point)
{
    bool returnValue = false;

    if (this->contains(point))
    {
        returnValue = true;
    }

    return returnValue;
}

void WedgeIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    const QPointF pos = event->pos();
    if (!iconPressed)
    {
        if (isIconPressed(pos))
        {
            iconPressed = true;
        }
    }
    event->accept();
}


void WedgeIcon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    const QPointF pos = event->pos();

    qDebug("You pressed on the icon. ");

    iconPressed = false;
    event->accept();
}
