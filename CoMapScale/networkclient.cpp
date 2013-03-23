#include <QNetworkConfigurationManager>
#include <QSettings>
#include <QNetworkSession>
#include <QMessageBox>

#include "networkclient.h"
#include "peerstate.h"

NetworkClient::NetworkClient()
    :QObject(0)
{
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(inDataReady()));
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(serverFound()));
}

NetworkClient::~NetworkClient()
{

}

void NetworkClient::sendPosition(double latitude, double longitude, double topLeftLat, double topLeftLong, double botRightLat, double botRightLong, qreal scale)
{
    QString text = tr("lat:%1,").arg(latitude, 0, 'f', 5) + tr("lon:%1,").arg(longitude, 0, 'f', 5);
    text += tr("tllat:%1,").arg(topLeftLat, 0, 'f', 5) + tr("tllon:%1,").arg(topLeftLong, 0, 'f', 5);
    text += tr("brlat:%1,").arg(botRightLat, 0, 'f', 5) + tr("brlon:%1,").arg(botRightLong, 0, 'f', 5);
    text += tr("scale:%1").arg(scale, 0, 'f', 3);

    sendMessage(text);
}

void NetworkClient::sendMessage(QString text)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << text;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    //qDebug() << "Sending message: " << text;

    tcpSocket.write(block);
}

void NetworkClient::inDataReady()
{
    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    int bytes;

    bytes = tcpSocket.bytesAvailable();

    while (bytes > 0 && blockSize == 0)
    {
        bytes = tcpSocket.bytesAvailable();
        if (bytes >= (int)sizeof(quint16))
        {
            in >> blockSize;

            bytes = tcpSocket.bytesAvailable();
            if (bytes >= blockSize)
            {
                QString text;
                in >> text;
                parseMessage(text);
                blockSize = 0;
            }
            else
            {
                qDebug() << "Too many bytes available";
            }
        }
        else
        {
            qDebug() << "Insufficient bytes available";
        }

        bytes = tcpSocket.bytesAvailable();
    }
}


void NetworkClient::parseMessage(QString message)
{
    QStringList elements = message.split(',');

    bool parseOK = true;
    int id = -1;
    int scale = -1;
    float lat = 0;
    float lon = 0;
    float vwLat = 0;
    float vwLon = 0;
    bool clientDisconnected = false;
    bool addHotel = false;
    bool addRestaurant = false;
    bool wedgeEnabledChanged = false;
    bool wedgeEnabled = true;
    bool objWedgeEnabledChanged = false;
    bool objWedgeEnabled = false;
    QString iconText;

    for (int i = 0; i < elements.size(); i++)
    {
        QString pair = elements.at(i);

        if (pair.startsWith("lat"))    //Current position latitude
        {
            QString latString = pair.remove(0, 4);
            lat = latString.toFloat(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing lat";
            }
        }
        else if (pair.startsWith("lon"))    //Position longitude
        {
            QString lonString = pair.remove(0, 4);
            lon = lonString.toFloat(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing lon";
            }

        }
        else if (pair.startsWith("vwLat"))    //Visit wear position latitude
        {
            QString latString = pair.remove(0, 6);
            vwLat = latString.toFloat(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing vwLat";
            }
        }
        else if (pair.startsWith("vwLon"))    //Visit wear position longitude
        {
            QString lonString = pair.remove(0, 6);
            vwLon = lonString.toFloat(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing vwLon";
            }

        }
        else if(pair.startsWith("dis"))
        {
            clientDisconnected = true;
        }
        else if (pair.startsWith("id"))  //Other client's id
        {
            QString idString = pair.remove(0, 3);
            id = idString.toInt(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing id";
            }
        } else if (pair.startsWith("scale"))  //Other client's scale
        {
            QString scaleString = pair.remove(0, 6);
            scale = scaleString.toInt(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing scale";
            }
        }
        else if (pair.startsWith("wedge") || pair.startsWith("nowedge"))
        {
            wedgeEnabledChanged = true;

            if (pair.startsWith("wedge"))
            {
                wedgeEnabled = true;
            }
            else
            {
                wedgeEnabled = false;
            }
        }
        else if (pair.startsWith("objw") || pair.startsWith("noobjw"))
        {
            objWedgeEnabledChanged = true;

            if (pair.startsWith("objw"))
            {
                objWedgeEnabled = true;
            }
            else
            {
                objWedgeEnabled = false;
            }
        }
        else if (pair.startsWith("hot"))    //Hotel
        {
            addHotel = true;
        }
        else if (pair.startsWith("res"))    //Hotel
        {
            addRestaurant = true;
        }
        else if (pair.startsWith("txt"))    //Icon text
        {
            iconText = pair.remove(0, 4);
        }
        else{
            //qDebug() << "Unrecognized message element: " << pair;
        }
    }

    if (parseOK)
    {
        QString peerId = QString::number(id);
        QGeoCoordinate location(lat, lon);

        if (clientDisconnected)
        {
            removePeer(peerId);
        }
        else if (wedgeEnabledChanged || objWedgeEnabledChanged)
        {
            emit wedgeStatusChanged(wedgeEnabled, objWedgeEnabled);
        }
        else if (addHotel)
        {
            emit newObjectAdded(MapMarker::HotelType, location, iconText);
        }
        else if (addRestaurant)
        {
            emit newObjectAdded(MapMarker::RestaurantType, location, iconText);
        }
        else if (lat != 0 || lon != 0 || scale != -1)
        {
            addPeer(peerId, location);
            updatePeer(peerId, location, scale);
            emit scaleChanged();
        }

        if (vwLat != 0 || vwLon != 0)
        {
            //Add visit wear
            QGeoCoordinate vwLocation(vwLat, vwLon);
            emit newVwAdded(peerId, vwLocation);
        }
        else if (id > -1)
        {
            this->clientId = QString::number(id);
        }

        emit requestRepaint();
        emit scaleChanged();

        //qDebug() << "Received update: " << message;
    }
    else
    {
        qDebug() << "Failed to parse incoming message: " << message;
    }
}

void NetworkClient::removePeer(QString id)
{
    MapMarker* marker;

    for (int i = 0; i < peerList.size(); i++)
    {
        PeerState peer = peerList.at(i);

        if (id.compare (peer.getPeerId()) == 0)
        {
            marker = peerList[i].getMarker();
            peerList.removeAt(i);
            emit peerDisconnected(marker);
        }
    }
}

void NetworkClient::addPeer(QString peerId, QGeoCoordinate coordinate)
{
    //Check if peer exists already
    bool peerFound = false;

    for (int i = 0; i < peerList.size(); i++)
    {
        PeerState peer = peerList.at(i);

        if (peerId.compare (peer.getPeerId()) == 0)
        {
            peerFound = true;
            break;
        }
    }

    //Add new peer if they aren't already in the list
    if (!peerFound)
    {
        PeerState newPeer = PeerState(peerId);
        scaleList[peerId.toInt()] = (int)newPeer.getZoomLevel();
        this->peerList.append(newPeer);

        emit newPeerAdded(peerId, coordinate);
        emit scaleChanged();
    }
}

void NetworkClient::updatePeer(QString id, QGeoCoordinate coordinate, int scale)
{
    for (int i = 0; i < peerList.size(); i++)
    {
        if (id.compare (peerList[i].getPeerId()) == 0)
        {
            peerList[i].setLastPosition(coordinate);
            scaleList[i]=scale;
            break;
        }
    }

    emit peerPositionChanged();
}

void NetworkClient::setPeerMarker(QString peerId, MapMarker *peerMarker)
{
    for (int i = 0; i < peerList.size(); i++)
    {
        if (peerId.compare (peerList[i].getPeerId()) == 0)
        {
            peerList[i].setMarker(peerMarker);
            break;
        }
    }
}

void NetworkClient::serverFound()
{
}

void NetworkClient::connectToServer()
{
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
    {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered)
        {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        networkSession->open();
    }

    blockSize = 0;
    //tcpSocket.abort();

#ifdef Q_WS_MAEMO_5
    //tcpSocket.connectToHost("130.179.30.148", 50000);
    tcpSocket.connectToHost("192.168.2.14", 50000);
#else
    tcpSocket.connectToHost("127.0.0.1", 50000); //For testing on desktop build
#endif
}

void NetworkClient::sessionOpened()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
}


void NetworkClient::displayError(QAbstractSocket::SocketError socketError)
{
    QMessageBox messageBox;

    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        messageBox.setWindowTitle (tr("CoMapOvi"));
        messageBox.setInformativeText (tr("The host has closed unexpectedly."));
        break;
    case QAbstractSocket::HostNotFoundError:
        messageBox.setWindowTitle (tr("CoMapOvi"));
        messageBox.setInformativeText (tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        messageBox.setWindowTitle (tr("CoMapOvi"));
        messageBox.setInformativeText (tr("The connection was refused by the peer. "
                                    "Make sure the CoMapOviServer is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        messageBox.setWindowTitle (tr("CoMapOvi"));
        messageBox.setInformativeText (tr("The following error occurred: %1.")
                                 .arg(tcpSocket.errorString()));
    }

    messageBox.exec();

}

int NetworkClient::getPeerScale(QString peerId){
    int peerID = peerId.toInt();
    return scaleList[0];

}
