/****************************************************************************
** Meta object code from reading C++ file 'imgProcessing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../imgProcessing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imgProcessing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_imgProcessing_t {
    QByteArrayData data[16];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_imgProcessing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_imgProcessing_t qt_meta_stringdata_imgProcessing = {
    {
QT_MOC_LITERAL(0, 0, 13), // "imgProcessing"
QT_MOC_LITERAL(1, 14, 7), // "fileNew"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 8), // "fileOpen"
QT_MOC_LITERAL(4, 32, 8), // "fileSave"
QT_MOC_LITERAL(5, 41, 10), // "fileSaveas"
QT_MOC_LITERAL(6, 52, 11), // "slot_combo1"
QT_MOC_LITERAL(7, 64, 11), // "slot_combo2"
QT_MOC_LITERAL(8, 76, 11), // "slot_combo3"
QT_MOC_LITERAL(9, 88, 11), // "slot_combo4"
QT_MOC_LITERAL(10, 100, 12), // "slot_button1"
QT_MOC_LITERAL(11, 113, 12), // "slot_button2"
QT_MOC_LITERAL(12, 126, 12), // "slot_button3"
QT_MOC_LITERAL(13, 139, 12), // "slot_button4"
QT_MOC_LITERAL(14, 152, 12), // "slot_button5"
QT_MOC_LITERAL(15, 165, 12) // "slot_spinbox"

    },
    "imgProcessing\0fileNew\0\0fileOpen\0"
    "fileSave\0fileSaveas\0slot_combo1\0"
    "slot_combo2\0slot_combo3\0slot_combo4\0"
    "slot_button1\0slot_button2\0slot_button3\0"
    "slot_button4\0slot_button5\0slot_spinbox"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_imgProcessing[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

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

       0        // eod
};

void imgProcessing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<imgProcessing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fileNew(); break;
        case 1: _t->fileOpen(); break;
        case 2: _t->fileSave(); break;
        case 3: _t->fileSaveas(); break;
        case 4: _t->slot_combo1(); break;
        case 5: _t->slot_combo2(); break;
        case 6: _t->slot_combo3(); break;
        case 7: _t->slot_combo4(); break;
        case 8: _t->slot_button1(); break;
        case 9: _t->slot_button2(); break;
        case 10: _t->slot_button3(); break;
        case 11: _t->slot_button4(); break;
        case 12: _t->slot_button5(); break;
        case 13: _t->slot_spinbox(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject imgProcessing::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_imgProcessing.data,
    qt_meta_data_imgProcessing,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *imgProcessing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *imgProcessing::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_imgProcessing.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int imgProcessing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
