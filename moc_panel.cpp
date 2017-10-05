/****************************************************************************
** Meta object code from reading C++ file 'panel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "panel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Panel_t {
    QByteArrayData data[10];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Panel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Panel_t qt_meta_stringdata_Panel = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Panel"
QT_MOC_LITERAL(1, 6, 10), // "disconnect"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 22), // "on_applyButton_clicked"
QT_MOC_LITERAL(4, 41, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(5, 65, 27), // "on_actionEspaniol_triggered"
QT_MOC_LITERAL(6, 93, 26), // "on_actionEnglish_triggered"
QT_MOC_LITERAL(7, 120, 29), // "on_actionDisconnect_triggered"
QT_MOC_LITERAL(8, 150, 10), // "showWindow"
QT_MOC_LITERAL(9, 161, 24) // "on_actionAbout_triggered"

    },
    "Panel\0disconnect\0\0on_applyButton_clicked\0"
    "on_actionQuit_triggered\0"
    "on_actionEspaniol_triggered\0"
    "on_actionEnglish_triggered\0"
    "on_actionDisconnect_triggered\0showWindow\0"
    "on_actionAbout_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Panel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Panel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Panel *_t = static_cast<Panel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->disconnect(); break;
        case 1: _t->on_applyButton_clicked(); break;
        case 2: _t->on_actionQuit_triggered(); break;
        case 3: _t->on_actionEspaniol_triggered(); break;
        case 4: _t->on_actionEnglish_triggered(); break;
        case 5: _t->on_actionDisconnect_triggered(); break;
        case 6: _t->showWindow(); break;
        case 7: _t->on_actionAbout_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Panel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::disconnect)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Panel::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Panel.data,
      qt_meta_data_Panel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Panel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Panel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Panel.stringdata0))
        return static_cast<void*>(const_cast< Panel*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Panel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Panel::disconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
