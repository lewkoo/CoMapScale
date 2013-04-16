#ifndef MAPPINGWIDGET_H
#define MAPPINGWIDGET_H

#include <QWidget>
//#include <QGeoMappingManager>
#include <qgeomappingmanager.h>
#include <QSlider>
#include <QString>

#include "networkclient.h"
#include "zoomslideritem.h"
#include "globalbutton.h"

QTM_USE_NAMESPACE

class GeoMap;
class QGraphicsView;
class ZoomButtonItem;
class ZoomSliderItem;
class ZoomStatusItem;
class MapMarker;

class MappingWidget : public QWidget
{
    Q_OBJECT
public:

    static bool wedgeIconsSwitch;
    static bool wedgeInteractivitySwitch;


    static QGraphicsScene* scene;
    static GeoMap* map;
    static MapMarker* returnMark;
    static qreal peerScale;
    static QGeoCoordinate peerCoordinates;
    explicit MappingWidget(QWidget *parent = 0);
    ~MappingWidget ();

    static QGraphicsScene *getScene();
    static void setPeerScale(qreal peerScaleIn);
    static void setPeerCoordinate(QGeoCoordinate peerCoordinatesIn);
    void processWedgeIconPress(Wedge* source);
    void processGlobalButtonIconPress();

    void mapPositionChanged();
    void mapPositionChangedWithClick(QString clickData);


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
    void adjustScale();
    void adjustSlider();

    void turnGlobalButton(bool isEnabled);
    void turnStatusSlider(bool isEnabled);
    void turnWedgeIcons(bool isEnabled);
    void turnWedgeInteractivity(bool isEnabled);




protected:
    void closeEvent(QCloseEvent *);

private:

    ZoomSliderItem* m_slider;
    ZoomStatusItem* s_slider;
    QGraphicsView* view;
    GlobalButton* globalButton;
    ZoomButtonItem* zoomButton;

    QString peerID;

    //for global button
    bool globalButtonPressed;
    QGeoCoordinate currLocation;
    qreal currScale;

    NetworkClient client;
};

#endif // MAPPINGWIDGET_H
