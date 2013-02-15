/****************************************************************************
** Meta object code from reading C++ file 'networkclient.h'
**
** Created: Sun Jun 3 17:47:57 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../networkclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NetworkClient[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      50,   32,   14,   14, 0x05,
      87,   14,   14,   14, 0x05,
     116,  109,   14,   14, 0x05,
     145,   32,   14,   14, 0x05,
     207,  180,   14,   14, 0x05,
     294,  268,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     336,  324,   14,   14, 0x08,
     379,   14,   14,   14, 0x08,
     395,   14,   14,   14, 0x08,
     409,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NetworkClient[] = {
    "NetworkClient\0\0requestRepaint()\0"
    "peerId,coordinate\0"
    "newPeerAdded(QString,QGeoCoordinate)\0"
    "peerPositionChanged()\0marker\0"
    "peerDisconnected(MapMarker*)\0"
    "newVwAdded(QString,QGeoCoordinate)\0"
    "markerType,coordinate,text\0"
    "newObjectAdded(MapMarker::MarkerType,QGeoCoordinate,QString)\0"
    "isEnabled,objWedgeEnabled\0"
    "wedgeStatusChanged(bool,bool)\0socketError\0"
    "displayError(QAbstractSocket::SocketError)\0"
    "sessionOpened()\0serverFound()\0"
    "inDataReady()\0"
};

const QMetaObject NetworkClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NetworkClient,
      qt_meta_data_NetworkClient, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NetworkClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NetworkClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NetworkClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkClient))
        return static_cast<void*>(const_cast< NetworkClient*>(this));
    return QObject::qt_metacast(_clname);
}

int NetworkClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: requestRepaint(); break;
        case 1: newPeerAdded((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 2: peerPositionChanged(); break;
        case 3: peerDisconnected((*reinterpret_cast< MapMarker*(*)>(_a[1]))); break;
        case 4: newVwAdded((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 5: newObjectAdded((*reinterpret_cast< MapMarker::MarkerType(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: wedgeStatusChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 8: sessionOpened(); break;
        case 9: serverFound(); break;
        case 10: inDataReady(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void NetworkClient::requestRepaint()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void NetworkClient::newPeerAdded(QString _t1, QGeoCoordinate _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NetworkClient::peerPositionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void NetworkClient::peerDisconnected(MapMarker * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void NetworkClient::newVwAdded(QString _t1, QGeoCoordinate _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void NetworkClient::newObjectAdded(MapMarker::MarkerType _t1, QGeoCoordinate _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void NetworkClient::wedgeStatusChanged(bool _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
