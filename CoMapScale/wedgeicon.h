#ifndef WEDGEICON_H
#define WEDGEICON_H

#include <QGraphicsRectItem>
#include <QPoint>

class MappingWidget;
class Wedge;
class QGraphicsSceneMouseEvent;

class WedgeIcon : public QGraphicsRectItem
{
public:
    explicit WedgeIcon(Wedge *parent);
    void setMappingWidget(MappingWidget* parent);

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    
public slots:

private:
    MappingWidget* mappingWidget;
    bool iconPressed;
    Wedge* parent;
    bool isIconPressed (const QPointF &point);
    
};

#endif // WEDGEICON_H
