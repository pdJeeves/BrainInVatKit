/****************************************************************************
** Meta object code from reading C++ file 'tractmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tractmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tractmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TractModel_t {
    QByteArrayData data[13];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TractModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TractModel_t qt_meta_stringdata_TractModel = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TractModel"
QT_MOC_LITERAL(1, 11, 16), // "toggleVisibility"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "editGene"
QT_MOC_LITERAL(4, 38, 9), // "edit_gene"
QT_MOC_LITERAL(5, 48, 10), // "LobeModel*"
QT_MOC_LITERAL(6, 59, 2), // "it"
QT_MOC_LITERAL(7, 62, 6), // "remove"
QT_MOC_LITERAL(8, 69, 4), // "save"
QT_MOC_LITERAL(9, 74, 5), // "FILE*"
QT_MOC_LITERAL(10, 80, 4), // "file"
QT_MOC_LITERAL(11, 85, 9), // "clearGene"
QT_MOC_LITERAL(12, 95, 14) // "TractSettings*"

    },
    "TractModel\0toggleVisibility\0\0editGene\0"
    "edit_gene\0LobeModel*\0it\0remove\0save\0"
    "FILE*\0file\0clearGene\0TractSettings*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TractModel[] = {

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
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    1,   46,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,
       8,    1,   50,    2, 0x0a /* Public */,
      11,    1,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,    6,

       0        // eod
};

void TractModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TractModel *_t = static_cast<TractModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toggleVisibility(); break;
        case 1: _t->editGene(); break;
        case 2: _t->edit_gene((*reinterpret_cast< LobeModel*(*)>(_a[1]))); break;
        case 3: _t->remove(); break;
        case 4: _t->save((*reinterpret_cast< FILE*(*)>(_a[1]))); break;
        case 5: _t->clearGene((*reinterpret_cast< TractSettings*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< LobeModel* >(); break;
            }
            break;
        }
    }
}

const QMetaObject TractModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TractModel.data,
      qt_meta_data_TractModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TractModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TractModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TractModel.stringdata0))
        return static_cast<void*>(const_cast< TractModel*>(this));
    return QObject::qt_metacast(_clname);
}

int TractModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
