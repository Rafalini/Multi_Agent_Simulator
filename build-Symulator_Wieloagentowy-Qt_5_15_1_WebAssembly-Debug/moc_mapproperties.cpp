/****************************************************************************
** Meta object code from reading C++ file 'mapproperties.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../client/headers/mapproperties.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapproperties.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MapProperties_t {
    QByteArrayData data[18];
    char stringdata0[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapProperties_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapProperties_t qt_meta_stringdata_MapProperties = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MapProperties"
QT_MOC_LITERAL(1, 14, 11), // "getSegments"
QT_MOC_LITERAL(2, 26, 38), // "QVector<std::shared_ptr<LineS..."
QT_MOC_LITERAL(3, 65, 0), // ""
QT_MOC_LITERAL(4, 66, 9), // "getPoints"
QT_MOC_LITERAL(5, 76, 32), // "QVector<std::shared_ptr<Point> >"
QT_MOC_LITERAL(6, 109, 9), // "getCities"
QT_MOC_LITERAL(7, 119, 31), // "QVector<std::shared_ptr<City> >"
QT_MOC_LITERAL(8, 151, 7), // "addCity"
QT_MOC_LITERAL(9, 159, 4), // "name"
QT_MOC_LITERAL(10, 164, 1), // "x"
QT_MOC_LITERAL(11, 166, 1), // "y"
QT_MOC_LITERAL(12, 168, 8), // "addPoint"
QT_MOC_LITERAL(13, 177, 10), // "addSegment"
QT_MOC_LITERAL(14, 188, 6), // "length"
QT_MOC_LITERAL(15, 195, 22), // "std::shared_ptr<Point>"
QT_MOC_LITERAL(16, 218, 8), // "begining"
QT_MOC_LITERAL(17, 227, 3) // "end"

    },
    "MapProperties\0getSegments\0"
    "QVector<std::shared_ptr<LineSegment> >\0"
    "\0getPoints\0QVector<std::shared_ptr<Point> >\0"
    "getCities\0QVector<std::shared_ptr<City> >\0"
    "addCity\0name\0x\0y\0addPoint\0addSegment\0"
    "length\0std::shared_ptr<Point>\0begining\0"
    "end"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapProperties[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,   44,    3, 0x02 /* Public */,
       4,    0,   45,    3, 0x02 /* Public */,
       6,    0,   46,    3, 0x02 /* Public */,
       8,    3,   47,    3, 0x02 /* Public */,
      12,    2,   54,    3, 0x02 /* Public */,
      13,    3,   59,    3, 0x02 /* Public */,

 // methods: parameters
    0x80000000 | 2,
    0x80000000 | 5,
    0x80000000 | 7,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,    9,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 15, 0x80000000 | 15,   14,   16,   17,

       0        // eod
};

void MapProperties::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MapProperties *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QVector<std::shared_ptr<LineSegment> > _r = _t->getSegments();
            if (_a[0]) *reinterpret_cast< QVector<std::shared_ptr<LineSegment> >*>(_a[0]) = std::move(_r); }  break;
        case 1: { QVector<std::shared_ptr<Point> > _r = _t->getPoints();
            if (_a[0]) *reinterpret_cast< QVector<std::shared_ptr<Point> >*>(_a[0]) = std::move(_r); }  break;
        case 2: { QVector<std::shared_ptr<City> > _r = _t->getCities();
            if (_a[0]) *reinterpret_cast< QVector<std::shared_ptr<City> >*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->addCity((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->addPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->addSegment((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::shared_ptr<Point>(*)>(_a[2])),(*reinterpret_cast< std::shared_ptr<Point>(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MapProperties::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MapProperties.data,
    qt_meta_data_MapProperties,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MapProperties::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapProperties::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MapProperties.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MapProperties::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
