#ifndef MAPPINGWIDGET_H
#define MAPPINGWIDGET_H

#include <QWidget>
//#include <QGeoMappingManager>
#include <qgeomappingmanager.h>

#include "networkclient.h"

QTM_USE_NAMESPACE

class GeoMap;
class QGraphicsView;
class ZoomButtonItem;
class MapMarker;

class MappingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MappingWidget(QWidget *parent = 0);
    ~MappingWidget ();

    void mapPositionChanged();

    MapMarker* addMapMarker(MapMarker::MarkerType markerType, QGeoCoordinate location);
    MapMarker* addMapMarker(MapMarker::MarkerType markerType, QGeoCoordinate location, QString text);

signals:

public slots:
    void initialize (QGeoMappingManager* mapManager);
    void addNewPeer (QString peerId, QGeoCoordinate coordinate);
    void updatePeerPositions ();
    void removeMapMarker(MapMarker* marker);
    void addNewVw (QString peerId, QGeoCoordinate coordinate);
    void addNewObject(MapMarker::MarkerType markerType, QGeoCoordinate coordinate, QString text);
    void setWedgeEnabled(bool isEnabled, bool objWedgeEnabled);

protected:
    void closeEvent(QCloseEvent *);

private:
    GeoMap* map;
    QGraphicsView* view;
    ZoomButtonItem* zoomButton;

    NetworkClient client;
};

#endif // MAPPINGWIDGET_H
