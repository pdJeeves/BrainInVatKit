/****************************************************************************
** Meta object code from reading C++ file 'lobegene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../lobegene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lobegene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LobeSettings_t {
    QByteArrayData data[11];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LobeSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LobeSettings_t qt_meta_stringdata_LobeSettings = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LobeSettings"
QT_MOC_LITERAL(1, 13, 10), // "closeEvent"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "QCloseEvent*"
QT_MOC_LITERAL(4, 38, 5), // "event"
QT_MOC_LITERAL(5, 44, 13), // "onClosePushed"
QT_MOC_LITERAL(6, 58, 13), // "onSelectColor"
QT_MOC_LITERAL(7, 72, 12), // "onTextEdited"
QT_MOC_LITERAL(8, 85, 11), // "onRelaxPrev"
QT_MOC_LITERAL(9, 97, 1), // "i"
QT_MOC_LITERAL(10, 99, 12) // "onRelaxState"

    },
    "LobeSettings\0closeEvent\0\0QCloseEvent*\0"
    "event\0onClosePushed\0onSelectColor\0"
    "onTextEdited\0onRelaxPrev\0i\0onRelaxState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LobeSettings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,
       8,    1,   50,    2, 0x0a /* Public */,
      10,    1,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void LobeSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LobeSettings *_t = static_cast<LobeSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: _t->onClosePushed(); break;
        case 2: _t->onSelectColor(); break;
        case 3: _t->onTextEdited(); break;
        case 4: _t->onRelaxPrev((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onRelaxState((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject LobeSettings::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LobeSettings.data,
      qt_meta_data_LobeSettings,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LobeSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LobeSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LobeSettings.stringdata0))
        return static_cast<void*>(const_cast< LobeSettings*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LobeSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
