#include <QGraphicsScene>
//#include <QGeoCoordinate>
#include <qgeocoordinate.h>
#include <QGraphicsView>
#include "global.h"
#include "mappingwidget.h"
#include "geomap.h"
#include "zoombuttonitem.h"
#include "mapoverlay.h"
#include <qgeoboundingbox.h>
#include "mapmarker.h"
#include "zoomslideritem.h"
#include "zoomstatusitem.h"

QTM_USE_NAMESPACE

QGraphicsScene* MappingWidget::scene = NULL;
GeoMap* MappingWidget::map = NULL;
MapMarker* MappingWidget::returnMark = NULL;

MappingWidget::MappingWidget(QWidget *parent) :
    QWidget(parent)
{
    this->map = NULL;
    this->view = NULL;

    connect(&client, SIGNAL(requestRepaint()), this, SLOT(repaint()));
    connect(&client, SIGNAL(newPeerAdded(QString, QGeoCoordinate)), this, SLOT(addNewPeer(QString, QGeoCoordinate)));
    connect(&client, SIGNAL(peerPositionChanged()), this, SLOT(updatePeerPositions()));
    connect(&client, SIGNAL(peerDisconnected(MapMarker*)), this, SLOT(removeMapMarker(MapMarker*)));
    connect(&client, SIGNAL(newVwAdded(QString,QGeoCoordinate)), this, SLOT(addNewVw(QString,QGeoCoordinate)));
    connect(&client, SIGNAL(newObjectAdded(MapMarker::MarkerType,QGeoCoordinate, QString)), this, SLOT(addNewObject(MapMarker::MarkerType,QGeoCoordinate, QString)));
    connect(&client, SIGNAL(wedgeStatusChanged(bool, bool)), this, SLOT(setWedgeEnabled(bool, bool)));
    connect(&client, SIGNAL(scaleChanged()), this, SLOT(adjustScale()));


}

MappingWidget::~MappingWidget()
{
    if (map != NULL)
        delete map;

    if (view != NULL)
        delete view;
}

void MappingWidget::closeEvent(QCloseEvent * event)
{
    event->accept();
}

void MappingWidget::initialize(QGeoMappingManager *mapManager)
{


    QRect viewportRect(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    map = new GeoMap (mapManager, this);

    scene = new QGraphicsScene;
    scene->addItem(map);

    //QList<QGraphicsGeoMap::ConnectivityMode> list = map->supportedConnectivityModes();
    //map->setConnectivityMode(QGraphicsGeoMap::OfflineMode); //Offline mode is not supported
    map->resize(viewportRect.width(), viewportRect.height());
    scene->setSceneRect(viewportRect);
    map->setCenter(QGeoCoordinate(48.854716, 2.346611));
    map->setZoomLevel(10);

    MapOverlay* overlay = new MapOverlay(map);
    map->addMapOverlay(overlay);

    view = new QGraphicsView(scene, this);
    view->resize(viewportRect.width(), viewportRect.height());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    s_slider = new ZoomStatusItem(map, this);//this order here matters
    m_slider = new ZoomSliderItem(map, this);

    connect(m_slider, SIGNAL(sliderPositionChanged()), this, SLOT(adjustSlider()));



    zoomButton = new ZoomButtonItem(map, m_slider);
    zoomButton->setRect(0, 0, 50, 100);
    scene->addItem(zoomButton);

    view->setVisible (true);
    view->setInteractive (true);

    //Connect to network server
    client.connectToServer();

    //Test
    addMapMarker(MapMarker::WedgePeerBlueType, QGeoCoordinate(48.854885, 2.346611));
    addMapMarker(MapMarker::PoiType, QGeoCoordinate(48.954885, 2.34661));
    addMapMarker(MapMarker::AnchorType, QGeoCoordinate(48.754885, 2.34661));
}

QGraphicsScene* MappingWidget::getScene(){
    return scene;
}

void MappingWidget::mapPositionChanged()
{
    map->updateWedges();

    QGeoBoundingBox viewportBox = map->viewport();
    QGeoCoordinate position = map->center();
    QGeoCoordinate topLeft = viewportBox.topLeft();
    QGeoCoordinate bottomRight = viewportBox.bottomRight();
    qreal scale = map->zoomLevel();
    adjustScale();

    client.sendPosition(position.latitude(), position.longitude(), topLeft.latitude(), topLeft.longitude(), bottomRight.latitude(), bottomRight.longitude(), scale);
}

MapMarker* MappingWidget::addMapMarker(MapMarker::MarkerType markerType, QGeoCoordinate location)
{
    return addMapMarker(markerType, location, "");
}

MapMarker* MappingWidget::addMapMarker(MapMarker::MarkerType markerType, QGeoCoordinate location, QString text)
{
    MapMarker* marker = new MapMarker(markerType, text);

    if(markerType == MapMarker::UndoType){
        returnMark = marker;
    }//saving undo mark pointer

    marker->setCoordinate(location);
    marker->setMappingWidget(this);
    map->addMapObject (marker);
    map->updateWedges();

    //Map takes ownership of marker, but the peer state needs a handle for position updates.
    return marker;
}

void MappingWidget::removeMapMarker(MapMarker *marker)
{
    map->removeMapObject(marker);
    map->updateWedges();
}

void MappingWidget::addNewPeer(QString peerId, QGeoCoordinate coordinate)
{
    MapMarker::MarkerType markerType = PeerState::getMarkerTypeById(peerId);
    MapMarker* peerMarker = addMapMarker(markerType, coordinate);
    client.setPeerMarker(peerId, peerMarker);
    this->peerID = peerId;

    map->updateWedges();
}

void MappingWidget::updatePeerPositions()
{
    map->updateWedges();
    adjustScale();
}

void MappingWidget::adjustScale(){
    //updates the peer's scale bar
    if(this->peerID != NULL){
    int peerScale = client.getPeerScale(this->peerID);
    s_slider->setSliderPosition(peerScale);
    }
}

void MappingWidget::adjustSlider(){
    adjustScale();
}

void MappingWidget::addNewVw(QString peerId, QGeoCoordinate coordinate)
{
    //int id = peerId.toInt();
    MapMarker::MarkerType markerType = PeerState::getVwMarkerTypeById(peerId);

    MapMarker* vwMarker = addMapMarker(markerType, coordinate); //TODO: save vwMarker in data structure for easier access than through map widget's object list
    map->updateWedges();
}

void MappingWidget::addNewObject(MapMarker::MarkerType markerType, QGeoCoordinate coordinate, QString text)
{
    addMapMarker(markerType, coordinate, text);
}

void MappingWidget::setWedgeEnabled(bool isEnabled, bool objWedgeEnabled)
{
    map->setWedgeEnabled(isEnabled, objWedgeEnabled);
}

void MappingWidget::processWedgeIconPress(Wedge *source){
    //create a return wedge icon on the centre
    if(source->getIconType()->getMarkerType() != MapMarker::UndoType){

    if(returnMark != NULL){
        returnMark->getWedge()->clearTheButton(); //removes the rectangle
        removeMapMarker(returnMark);
    }


    addMapMarker(MapMarker::UndoType, map->center());

    map->setCenter(map->screenPositionToCoordinate(source->getTarget()));
    map->updateWedges();
    }else{
        //hit the undo button
        if(returnMark != NULL){
            returnMark->getWedge()->clearTheButton(); //removes the rectangle
            removeMapMarker(returnMark);
        }



        map->setCenter(map->screenPositionToCoordinate(source->getTarget()));
        map->updateWedges();
    }


}
