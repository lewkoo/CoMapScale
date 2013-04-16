#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QTcpSocket>
#include <QList>
#include "peerstate.h"
#include "mapmarker.h"

class QNetworkSession;

class NetworkClient: public QObject
{
    Q_OBJECT

public:
    NetworkClient();
    ~NetworkClient();

    void connectToServer();
    void disconnectFromServer();
    void sendClick(MapMarker *type);
    void sendPosition(double latitude, double longitude, double topLeftLat, double topLeftLong, double botRightLat, double botRightLong, qreal scale);
    void sendPosition(double latitude, double longitude, double topLeftLat, double topLeftLong, double botRightLat, double botRightLong, qreal scale, QString clickData);
    void setPeerMarker(QString peerId, MapMarker* peerMarker);
    int getPeerScale(QString peerId);

private:
    void parseMessage(QString message);
    void sendMessage(QString text);
    void removePeer(QString id);
    void addPeer(QString id, QGeoCoordinate coordinate);
    void updatePeer(QString id, QGeoCoordinate coordinate, int scale);

signals:
    void requestRepaint();
    void newPeerAdded(QString peerId, QGeoCoordinate coordinate);
    void peerPositionChanged();
    void peerDisconnected(MapMarker* marker);
    void newVwAdded(QString peerId, QGeoCoordinate coordinate);
    void newObjectAdded(MapMarker::MarkerType markerType, QGeoCoordinate coordinate, QString text);
    void wedgeStatusChanged(bool isEnabled, bool objWedgeEnabled);
    void scaleChanged();

    void newPeerScale(qreal newScale);
    void newPeerCoordinate(QGeoCoordinate newCoordinate);
    void togleGlobalButtonSig(bool isEnabled);
    void togleStatusSliderSig(bool isEnabled);
    void togleWedgeIcons(bool isEnabled);
    void togleWedgeInteractivity(bool isEnabled);

private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void sessionOpened();
    void serverFound();
    void inDataReady();

private:
    QTcpSocket tcpSocket;
    QNetworkSession* networkSession;
    quint16 blockSize;
    QList<PeerState> peerList;
    QString clientId;
    int scaleList[2];

    bool globalEnabled;
    bool statusSliderEnabled;
    bool wedgeIconsEnabled;
    bool wedgePressesEnabled;

};

#endif // NETWORKCLIENT_H
