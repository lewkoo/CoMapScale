#include "wedgeicon.h"
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "mappingwidget.h"



WedgeIcon::WedgeIcon(Wedge *parent) :
    QGraphicsRectItem()
{
    iconPressed = false;
    this->parent = parent;
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
    if(iconPressed == true){
    const QPointF pos = event->pos();

    //send a message to the Wedge
    //wedge shall handle the request to the Map
    //map shall create an return icon on its centre
    //map shall adjust itself

    if(mappingWidget != NULL)
        mappingWidget->processWedgeIconPress(parent);

    iconPressed = false;
    event->accept();
    }
}

void WedgeIcon::setMappingWidget(MappingWidget *parent){
    this->mappingWidget = parent;
}
