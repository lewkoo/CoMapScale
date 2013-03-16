#ifndef WEDGEICON_H
#define WEDGEICON_H

#include <QGraphicsRectItem>
#include <QPoint>

class QGraphicsSceneMouseEvent;

class WedgeIcon : public QGraphicsRectItem
{
public:
    explicit WedgeIcon();

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    
public slots:

private:
    bool iconPressed;
    bool isIconPressed (const QPointF &point);
    
};

#endif // WEDGEICON_H
