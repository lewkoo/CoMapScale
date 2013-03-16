#ifndef MAPPINGWIDGET_H
#define MAPPINGWIDGET_H

#include <QWidget>
//#include <QGeoMappingManager>
#include <qgeomappingmanager.h>
#include <QSlider>

#include "networkclient.h"

QTM_USE_NAMESPACE

class GeoMap;
class QGraphicsView;
class ZoomButtonItem;
class ZoomSliderItem;
class MapMarker;

class MappingWidget : public QWidget
{
    Q_OBJECT
public:
    static QGraphicsScene* scene;
    explicit MappingWidget(QWidget *parent = 0);
    ~MappingWidget ();

    static QGraphicsScene *getScene();
    static void processWedgeIconPress(Wedge* source);

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
    ZoomSliderItem* m_slider;
    QGraphicsView* view;
    ZoomButtonItem* zoomButton;


    NetworkClient client;
};

#endif // MAPPINGWIDGET_H
