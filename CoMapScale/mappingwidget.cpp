#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QEventLoop>
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
#include "globalbutton.h"
#include "zoomstatusicon.h"

QTM_USE_NAMESPACE

QGraphicsScene* MappingWidget::scene = NULL;
GeoMap* MappingWidget::map = NULL;
MapMarker* MappingWidget::returnMark = NULL;
qreal MappingWidget::peerScale = NULL;
QGeoCoordinate MappingWidget::peerCoordinates;
bool MappingWidget::wedgeIconsSwitch;
bool MappingWidget::wedgeInteractivitySwitch;


const int MappingWidget::NUM_TEST_MOVES = 1000;

MappingWidget::MappingWidget(QWidget *parent) :
    QWidget(parent)
{
    this->map = NULL;
    this->view = NULL;
    globalButtonPressed = false;
    wedgeIconsSwitch = true;
    wedgeInteractivitySwitch = true;

    connect(&client, SIGNAL(requestRepaint()), this, SLOT(repaint()));
    connect(&client, SIGNAL(newPeerAdded(QString, QGeoCoordinate)), this, SLOT(addNewPeer(QString, QGeoCoordinate)));
    connect(&client, SIGNAL(peerPositionChanged()), this, SLOT(updatePeerPositions()));
    connect(&client, SIGNAL(peerDisconnected(MapMarker*)), this, SLOT(removeMapMarker(MapMarker*)));
    connect(&client, SIGNAL(newVwAdded(QString,QGeoCoordinate)), this, SLOT(addNewVw(QString,QGeoCoordinate)));
    connect(&client, SIGNAL(newObjectAdded(MapMarker::MarkerType,QGeoCoordinate, QString)), this, SLOT(addNewObject(MapMarker::MarkerType,QGeoCoordinate, QString)));
    connect(&client, SIGNAL(wedgeStatusChanged(bool, bool)), this, SLOT(setWedgeEnabled(bool, bool)));
    connect(&client, SIGNAL(scaleChanged()), this, SLOT(adjustScale()));

    connect(&client, SIGNAL(newPeerScale(qreal)), this, SLOT(setPeerScale(qreal)));
    connect(&client, SIGNAL(newPeerCoordinate(QGeoCoordinate)), this, SLOT(setPeerCoordinate(QGeoCoordinate)));


    connect(&client,SIGNAL(togleGlobalButtonSig(bool)), this, SLOT(turnGlobalButton(bool)));
    connect(&client, SIGNAL(togleStatusSliderSig(bool)),this,SLOT(turnStatusSlider(bool)));
    connect(&client, SIGNAL(togleWedgeIcons(bool)), this, SLOT(turnWedgeIcons(bool)));
    connect(&client, SIGNAL(togleWedgeInteractivity(bool)), this, SLOT(turnWedgeInteractivity(bool)));

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

    globalButton = NULL;
    statusIcon = NULL;

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
    s_slider->setVisible(false);
    //m_slider->setMaximum(map->maximumZoomLevel());
    //m_slider->setSliderPosition(map->zoomLevel());
    m_slider = new ZoomSliderItem(map, this);
    m_slider->setEnabled(false);
    m_slider->setMouseTracking(false);
    m_slider->setTracking(false);

    connect(m_slider, SIGNAL(sliderPositionChanged()), this, SLOT(adjustSlider()));



    zoomButton = new ZoomButtonItem(map, m_slider);
    zoomButton->setRect(660,80, 50, 250);
    scene->addItem(zoomButton);

    view->setVisible (true);
    view->setInteractive (true);

    globalButton = new GlobalButton(map, "0", this);
    globalButton->setRect(660,37,50,35);
    scene->addItem(globalButton);

    statusIcon = new zoomstatusicon(map,m_slider, "peerID", this);
    statusIcon->setRect(610,102,0,0);
    scene->addItem(statusIcon);


    //Connect to network server
    client.connectToServer();

    //add global button


    //Test
    //addMapMarker(MapMarker::HotelType, QGeoCoordinate(48.854885, 2.346611));
    //addMapMarker(MapMarker::PoiType, QGeoCoordinate(48.954885, 2.34661));
    //addMapMarker(MapMarker::AnchorType, QGeoCoordinate(48.754885, 2.34661));


    //runServerLoggingTests();
    //sleepFor(10);


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
    adjustScale();
    qreal scale = map->zoomLevel();



    client.sendPosition(position.latitude(), position.longitude(), topLeft.latitude(), topLeft.longitude(), bottomRight.latitude(), bottomRight.longitude(), scale);
}

void MappingWidget::mapPositionChangedWithClick(QString clickData){
    map->updateWedges();

    QGeoBoundingBox viewportBox = map->viewport();
    QGeoCoordinate position = map->center();
    QGeoCoordinate topLeft = viewportBox.topLeft();
    QGeoCoordinate bottomRight = viewportBox.bottomRight();
    adjustScale();
    qreal scale = map->zoomLevel();



    client.sendPosition(position.latitude(), position.longitude(), topLeft.latitude(), topLeft.longitude(), bottomRight.latitude(), bottomRight.longitude(), scale, clickData);
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


    statusIcon->setPeerID(peerID);




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
    int temp = abs(m_slider->sliderPosition()-peerScale);
    m_slider->setPageStep(temp);

    statusIcon->setPosition(peerScale);

    map->updateWedges();




    //qDebug( QString::number(temp).toAscii() ) ;
    }
}

void MappingWidget::adjustSlider(){
    adjustScale();




    QGeoBoundingBox viewportBox = map->viewport();
    QGeoCoordinate position = map->center();
    QGeoCoordinate topLeft = viewportBox.topLeft();
    QGeoCoordinate bottomRight = viewportBox.bottomRight();
    qreal scale = map->zoomLevel();
    adjustScale();
    client.sendPosition(position.latitude(), position.longitude(), topLeft.latitude(), topLeft.longitude(), bottomRight.latitude(), bottomRight.longitude(), scale);

    //client.sendPosition(position.latitude(), position.longitude(), topLeft.latitude(), topLeft.longitude(), bottomRight.latitude(), bottomRight.longitude(), scale);

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
    //log an icon click

    if(wedgeInteractivitySwitch == true){

    MapMarker *temp = source->getIconType();
    QString clickData = temp->markerToString(temp->getMarkerType());

    QGeoCoordinate tempCoordinate = source->getWedgeTargetIcon()->coordinate();

    //create a return wedge icon on the centre
    if(source->getIconType()->getMarkerType() != MapMarker::WedgeUndoType){

    if(returnMark != NULL){
        returnMark->getWedge()->clearTheButton(); //removes the rectangle
        removeMapMarker(returnMark);
    }


    addMapMarker(MapMarker::UndoType, map->center());

    map->setLastClickedButton(clickData);
    map->setCenter(tempCoordinate);
    map->updateWedges();

    }else{
        //hit the undo button
        map->setCenter(tempCoordinate);
        map->updateWedges();

        returnMark->getWedge()->clearTheButton(); //removes the rectangle
        removeMapMarker(returnMark);


        }
    }

}

void MappingWidget::processGlobalButtonIconPress(){
    //take the current scale and position
    if(globalButtonPressed == false){
        //save your current location & scale
        currLocation = map->center();
        currScale = map->zoomLevel();

        //set yor current location & scale to the other users
        map->setCenter(peerCoordinates);
        m_slider->buttonPressed((int)peerScale);
        adjustSlider();
        globalButton->setToUndo();
        globalButtonPressed = true;

        //send click data



        QString clickData = "GlobalButton";
        mapPositionChangedWithClick(clickData);
    }else{

        map->setCenter(currLocation);

        m_slider->buttonPressed((int)currScale);
        adjustSlider();

        globalButton->setToPeerIcon();
        globalButtonPressed = false;

        QString clickData = "GlobalButton";
        mapPositionChangedWithClick(clickData);
    }


    //update the global button to display undo icon

}


void MappingWidget::setPeerScale(qreal peerScaleIn){
   peerScale = peerScaleIn;

   processWizzyWiz();

   //qDebug() << "New scale received: " + (QString::number(peerScale)) + "\n";
}

void MappingWidget::setPeerCoordinate(QGeoCoordinate peerCoordinatesIn){
    if(peerCoordinates != peerCoordinatesIn){
        peerCoordinates = peerCoordinatesIn;
        processWizzyWiz();
    }

    //qDebug() << "New coordinates received";
}


void MappingWidget::turnGlobalButton(bool isEnabled){

    if(globalButton != NULL){

    if(isEnabled == false){
    globalButton->setVisible(false);
    }else{
        globalButton->setVisible(true);
    }
    }
}

void MappingWidget::turnStatusSlider(bool isEnabled){


    if(isEnabled == false){
    s_slider->setVisible(false);
    statusIcon->setVisible(false);
    }else{
        //s_slider->setVisible(true);
        statusIcon->setVisible(true);
    }

}

void MappingWidget::turnWedgeIcons(bool isEnabled){
    if(isEnabled == false){
        wedgeIconsSwitch = false;
        wedgeInteractivitySwitch = false;
        //disable interactivity
    }else{
        wedgeIconsSwitch = true;
        //enable interactivity - might want to do that
    }
}

void MappingWidget::turnWedgeInteractivity(bool isEnabled){
    if(isEnabled == false){

        wedgeInteractivitySwitch = false;
        //disable interactivity
    }else{
        wedgeInteractivitySwitch = true;
        //enable interactivity
    }
}

void MappingWidget::processWizzyWiz(){
    if(globalButtonPressed == true){
        map->setCenter(peerCoordinates);
        m_slider->buttonPressed((int)peerScale);
        //mapPositionChanged();
    }
}

bool MappingWidget::isGlobalButtonPressed(){
    return globalButtonPressed;
}

void MappingWidget::resetWizzyWizMode(){
    if(globalButtonPressed == true){
        //break ouf of wizzy wiz mode
        globalButtonPressed = false;
        globalButton->setToPeerIcon();
    }
}

void MappingWidget::runServerLoggingTests(){

    int i = 0;

    QGeoCoordinate coordinate1(48.954885, 2.34661);
    QGeoCoordinate coordinate2(48.754885, 2.34661);

    while (i < MappingWidget::NUM_TEST_MOVES){

        if(i%2 == 0){
            //set position to one place
            map->setCenter(coordinate1);
            mapPositionChanged();
        }else{
            //set position to other place
            map->setCenter(coordinate2);
            mapPositionChanged();
        }

        sleepFor(2);
        i++;
    }


}

void MappingWidget::sleepFor(int timeToWait){
        //sleeping for x msecs
        QTimer timer;
        timer.start(timeToWait);
        QEventLoop loop;
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        loop.exec();
}

void MappingWidget::processZoomStatusButtonPress(){
    QString clickData = "SliderButton";
    mapPositionChangedWithClick(clickData);
}
