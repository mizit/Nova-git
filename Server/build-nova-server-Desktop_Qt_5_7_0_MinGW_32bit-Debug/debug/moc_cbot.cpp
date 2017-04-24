/****************************************************************************
** Meta object code from reading C++ file 'cbot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../nova-server/cbot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cbot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CBot_t {
    QByteArrayData data[5];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CBot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CBot_t qt_meta_stringdata_CBot = {
    {
QT_MOC_LITERAL(0, 0, 4), // "CBot"
QT_MOC_LITERAL(1, 5, 9), // "GonnaDead"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 14), // "ExecuteCommand"
QT_MOC_LITERAL(4, 31, 6) // "Update"

    },
    "CBot\0GonnaDead\0\0ExecuteCommand\0Update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CBot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CBot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CBot *_t = static_cast<CBot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GonnaDead(); break;
        case 1: _t->ExecuteCommand(); break;
        case 2: _t->Update(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CBot::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CBot::GonnaDead)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CBot::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CBot.data,
      qt_meta_data_CBot,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CBot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CBot::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CBot.stringdata0))
        return static_cast<void*>(const_cast< CBot*>(this));
    return QObject::qt_metacast(_clname);
}

int CBot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CBot::GonnaDead()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_CHyperMind_t {
    QByteArrayData data[11];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CHyperMind_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CHyperMind_t qt_meta_stringdata_CHyperMind = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CHyperMind"
QT_MOC_LITERAL(1, 11, 7), // "BotDead"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 11), // "MinerCreate"
QT_MOC_LITERAL(4, 32, 14), // "CarryallCreate"
QT_MOC_LITERAL(5, 47, 13), // "AnomalyCreate"
QT_MOC_LITERAL(6, 61, 12), // "FinderCreate"
QT_MOC_LITERAL(7, 74, 10), // "ComAddBack"
QT_MOC_LITERAL(8, 85, 8), // "ComAddGo"
QT_MOC_LITERAL(9, 94, 10), // "ComAddDrop"
QT_MOC_LITERAL(10, 105, 12) // "ComAddAttack"

    },
    "CHyperMind\0BotDead\0\0MinerCreate\0"
    "CarryallCreate\0AnomalyCreate\0FinderCreate\0"
    "ComAddBack\0ComAddGo\0ComAddDrop\0"
    "ComAddAttack"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CHyperMind[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CHyperMind::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CHyperMind *_t = static_cast<CHyperMind *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->BotDead(); break;
        case 1: _t->MinerCreate(); break;
        case 2: _t->CarryallCreate(); break;
        case 3: _t->AnomalyCreate(); break;
        case 4: _t->FinderCreate(); break;
        case 5: _t->ComAddBack(); break;
        case 6: _t->ComAddGo(); break;
        case 7: _t->ComAddDrop(); break;
        case 8: _t->ComAddAttack(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CHyperMind::staticMetaObject = {
    { &CBot::staticMetaObject, qt_meta_stringdata_CHyperMind.data,
      qt_meta_data_CHyperMind,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CHyperMind::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CHyperMind::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CHyperMind.stringdata0))
        return static_cast<void*>(const_cast< CHyperMind*>(this));
    return CBot::qt_metacast(_clname);
}

int CHyperMind::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CBot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
