/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../nova-server/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "newUser"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 14), // "slotReadClient"
QT_MOC_LITERAL(4, 35, 10), // "UserCreate"
QT_MOC_LITERAL(5, 46, 10), // "DataUpdate"
QT_MOC_LITERAL(6, 57, 8), // "DataSave"
QT_MOC_LITERAL(7, 66, 16), // "UserDisconnected"
QT_MOC_LITERAL(8, 83, 4), // "pbtn"
QT_MOC_LITERAL(9, 88, 7), // "LockPos"
QT_MOC_LITERAL(10, 96, 6), // "SetPos"
QT_MOC_LITERAL(11, 103, 7), // "ItemAdd"
QT_MOC_LITERAL(12, 111, 7), // "ItemDel"
QT_MOC_LITERAL(13, 119, 10), // "UserChange"
QT_MOC_LITERAL(14, 130, 9), // "HpRestore"
QT_MOC_LITERAL(15, 140, 10), // "OxyRestore"
QT_MOC_LITERAL(16, 151, 15), // "DevourerTimeout"
QT_MOC_LITERAL(17, 167, 11), // "SendMessage"
QT_MOC_LITERAL(18, 179, 9), // "BlindSend"
QT_MOC_LITERAL(19, 189, 13) // "SetDevourTime"

    },
    "MainWindow\0newUser\0\0slotReadClient\0"
    "UserCreate\0DataUpdate\0DataSave\0"
    "UserDisconnected\0pbtn\0LockPos\0SetPos\0"
    "ItemAdd\0ItemDel\0UserChange\0HpRestore\0"
    "OxyRestore\0DevourerTimeout\0SendMessage\0"
    "BlindSend\0SetDevourTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08 /* Private */,
       3,    0,  105,    2, 0x08 /* Private */,
       4,    0,  106,    2, 0x08 /* Private */,
       5,    0,  107,    2, 0x08 /* Private */,
       6,    0,  108,    2, 0x08 /* Private */,
       7,    0,  109,    2, 0x08 /* Private */,
       8,    0,  110,    2, 0x08 /* Private */,
       9,    0,  111,    2, 0x08 /* Private */,
      10,    0,  112,    2, 0x08 /* Private */,
      11,    0,  113,    2, 0x08 /* Private */,
      12,    0,  114,    2, 0x08 /* Private */,
      13,    0,  115,    2, 0x08 /* Private */,
      14,    0,  116,    2, 0x08 /* Private */,
      15,    0,  117,    2, 0x08 /* Private */,
      16,    0,  118,    2, 0x08 /* Private */,
      17,    0,  119,    2, 0x08 /* Private */,
      18,    0,  120,    2, 0x08 /* Private */,
      19,    0,  121,    2, 0x08 /* Private */,

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

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newUser(); break;
        case 1: _t->slotReadClient(); break;
        case 2: _t->UserCreate(); break;
        case 3: _t->DataUpdate(); break;
        case 4: _t->DataSave(); break;
        case 5: _t->UserDisconnected(); break;
        case 6: _t->pbtn(); break;
        case 7: _t->LockPos(); break;
        case 8: _t->SetPos(); break;
        case 9: _t->ItemAdd(); break;
        case 10: _t->ItemDel(); break;
        case 11: _t->UserChange(); break;
        case 12: _t->HpRestore(); break;
        case 13: _t->OxyRestore(); break;
        case 14: _t->DevourerTimeout(); break;
        case 15: _t->SendMessage(); break;
        case 16: _t->BlindSend(); break;
        case 17: _t->SetDevourTime(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
