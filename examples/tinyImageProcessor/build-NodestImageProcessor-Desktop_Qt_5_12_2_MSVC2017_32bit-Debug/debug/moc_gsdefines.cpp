/****************************************************************************
** Meta object code from reading C++ file 'gsdefines.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../NodestImageProcessor/gsdefines.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gsdefines.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Nodest__QStringSetter_t {
    QByteArrayData data[4];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Nodest__QStringSetter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Nodest__QStringSetter_t qt_meta_stringdata_Nodest__QStringSetter = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Nodest::QStringSetter"
QT_MOC_LITERAL(1, 22, 12), // "receiveValue"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5) // "value"

    },
    "Nodest::QStringSetter\0receiveValue\0\0"
    "value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Nodest__QStringSetter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void Nodest::QStringSetter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QStringSetter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveValue((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Nodest::QStringSetter::staticMetaObject = { {
    &AbstractSlotSetter::staticMetaObject,
    qt_meta_stringdata_Nodest__QStringSetter.data,
    qt_meta_data_Nodest__QStringSetter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Nodest::QStringSetter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Nodest::QStringSetter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Nodest__QStringSetter.stringdata0))
        return static_cast<void*>(this);
    return AbstractSlotSetter::qt_metacast(_clname);
}

int Nodest::QStringSetter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractSlotSetter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_Nodest__IntSetter_t {
    QByteArrayData data[4];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Nodest__IntSetter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Nodest__IntSetter_t qt_meta_stringdata_Nodest__IntSetter = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Nodest::IntSetter"
QT_MOC_LITERAL(1, 18, 12), // "receiveValue"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5) // "value"

    },
    "Nodest::IntSetter\0receiveValue\0\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Nodest__IntSetter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void Nodest::IntSetter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IntSetter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveValue((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Nodest::IntSetter::staticMetaObject = { {
    &AbstractSlotSetter::staticMetaObject,
    qt_meta_stringdata_Nodest__IntSetter.data,
    qt_meta_data_Nodest__IntSetter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Nodest::IntSetter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Nodest::IntSetter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Nodest__IntSetter.stringdata0))
        return static_cast<void*>(this);
    return AbstractSlotSetter::qt_metacast(_clname);
}

int Nodest::IntSetter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractSlotSetter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_Nodest__QImageGetter_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Nodest__QImageGetter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Nodest__QImageGetter_t qt_meta_stringdata_Nodest__QImageGetter = {
    {
QT_MOC_LITERAL(0, 0, 20) // "Nodest::QImageGetter"

    },
    "Nodest::QImageGetter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Nodest__QImageGetter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Nodest::QImageGetter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Nodest::QImageGetter::staticMetaObject = { {
    &AbstractSlotGetter::staticMetaObject,
    qt_meta_stringdata_Nodest__QImageGetter.data,
    qt_meta_data_Nodest__QImageGetter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Nodest::QImageGetter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Nodest::QImageGetter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Nodest__QImageGetter.stringdata0))
        return static_cast<void*>(this);
    return AbstractSlotGetter::qt_metacast(_clname);
}

int Nodest::QImageGetter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractSlotGetter::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
