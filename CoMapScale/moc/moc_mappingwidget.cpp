/****************************************************************************
** Meta object code from reading C++ file 'mappingwidget.h'
**
** Created: Fri Apr 26 15:36:46 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mappingwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mappingwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MappingWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   15,   14,   14, 0x0a,
      76,   58,   14,   14, 0x0a,
     111,   14,   14,   14, 0x0a,
     140,  133,   14,   14, 0x0a,
     168,   58,   14,   14, 0x0a,
     228,  201,   14,   14, 0x0a,
     313,  287,   14,   14, 0x0a,
     340,   14,   14,   14, 0x0a,
     354,   14,   14,   14, 0x0a,
     379,  369,   14,   14, 0x0a,
     402,  369,   14,   14, 0x0a,
     425,  369,   14,   14, 0x0a,
     446,  369,   14,   14, 0x0a,
     487,  475,   14,   14, 0x0a,
     525,  507,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MappingWidget[] = {
    "MappingWidget\0\0mapManager\0"
    "initialize(QGeoMappingManager*)\0"
    "peerId,coordinate\0addNewPeer(QString,QGeoCoordinate)\0"
    "updatePeerPositions()\0marker\0"
    "removeMapMarker(MapMarker*)\0"
    "addNewVw(QString,QGeoCoordinate)\0"
    "markerType,coordinate,text\0"
    "addNewObject(MapMarker::MarkerType,QGeoCoordinate,QString)\0"
    "isEnabled,objWedgeEnabled\0"
    "setWedgeEnabled(bool,bool)\0adjustScale()\0"
    "adjustSlider()\0isEnabled\0"
    "turnGlobalButton(bool)\0turnStatusSlider(bool)\0"
    "turnWedgeIcons(bool)\0turnWedgeInteractivity(bool)\0"
    "peerScaleIn\0setPeerScale(qreal)\0"
    "peerCoordinatesIn\0setPeerCoordinate(QGeoCoordinate)\0"
};

const QMetaObject MappingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MappingWidget,
      qt_meta_data_MappingWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MappingWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MappingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MappingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MappingWidget))
        return static_cast<void*>(const_cast< MappingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MappingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: initialize((*reinterpret_cast< QGeoMappingManager*(*)>(_a[1]))); break;
        case 1: addNewPeer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 2: updatePeerPositions(); break;
        case 3: removeMapMarker((*reinterpret_cast< MapMarker*(*)>(_a[1]))); break;
        case 4: addNewVw((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 5: addNewObject((*reinterpret_cast< MapMarker::MarkerType(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: setWedgeEnabled((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: adjustScale(); break;
        case 8: adjustSlider(); break;
        case 9: turnGlobalButton((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: turnStatusSlider((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: turnWedgeIcons((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: turnWedgeInteractivity((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: setPeerScale((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 14: setPeerCoordinate((*reinterpret_cast< QGeoCoordinate(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
