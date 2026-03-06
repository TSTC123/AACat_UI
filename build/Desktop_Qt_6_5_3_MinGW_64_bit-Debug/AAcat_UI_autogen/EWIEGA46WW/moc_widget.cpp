/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../widget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSCatUIENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSCatUIENDCLASS = QtMocHelpers::stringData(
    "CatUI",
    "onAvatarClicked",
    "",
    "updateAvatar",
    "pixmap",
    "onUsernameClicked",
    "onUsernameEditingFinished",
    "onCycleValueChanged",
    "onTotalValueChanged",
    "sendMessage",
    "clearChat",
    "getCurrentTime"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCatUIENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[6];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[7];
    char stringdata5[18];
    char stringdata6[26];
    char stringdata7[20];
    char stringdata8[20];
    char stringdata9[12];
    char stringdata10[10];
    char stringdata11[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCatUIENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCatUIENDCLASS_t qt_meta_stringdata_CLASSCatUIENDCLASS = {
    {
        QT_MOC_LITERAL(0, 5),  // "CatUI"
        QT_MOC_LITERAL(6, 15),  // "onAvatarClicked"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 12),  // "updateAvatar"
        QT_MOC_LITERAL(36, 6),  // "pixmap"
        QT_MOC_LITERAL(43, 17),  // "onUsernameClicked"
        QT_MOC_LITERAL(61, 25),  // "onUsernameEditingFinished"
        QT_MOC_LITERAL(87, 19),  // "onCycleValueChanged"
        QT_MOC_LITERAL(107, 19),  // "onTotalValueChanged"
        QT_MOC_LITERAL(127, 11),  // "sendMessage"
        QT_MOC_LITERAL(139, 9),  // "clearChat"
        QT_MOC_LITERAL(149, 14)   // "getCurrentTime"
    },
    "CatUI",
    "onAvatarClicked",
    "",
    "updateAvatar",
    "pixmap",
    "onUsernameClicked",
    "onUsernameEditingFinished",
    "onCycleValueChanged",
    "onTotalValueChanged",
    "sendMessage",
    "clearChat",
    "getCurrentTime"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCatUIENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    1,   69,    2, 0x08,    2 /* Private */,
       5,    0,   72,    2, 0x08,    4 /* Private */,
       6,    0,   73,    2, 0x08,    5 /* Private */,
       7,    0,   74,    2, 0x08,    6 /* Private */,
       8,    0,   75,    2, 0x08,    7 /* Private */,
       9,    0,   76,    2, 0x08,    8 /* Private */,
      10,    0,   77,    2, 0x08,    9 /* Private */,
      11,    0,   78,    2, 0x08,   10 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,

       0        // eod
};

Q_CONSTINIT const QMetaObject CatUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSCatUIENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCatUIENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCatUIENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CatUI, std::true_type>,
        // method 'onAvatarClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateAvatar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPixmap &, std::false_type>,
        // method 'onUsernameClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onUsernameEditingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCycleValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTotalValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearChat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getCurrentTime'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void CatUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CatUI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onAvatarClicked(); break;
        case 1: _t->updateAvatar((*reinterpret_cast< std::add_pointer_t<QPixmap>>(_a[1]))); break;
        case 2: _t->onUsernameClicked(); break;
        case 3: _t->onUsernameEditingFinished(); break;
        case 4: _t->onCycleValueChanged(); break;
        case 5: _t->onTotalValueChanged(); break;
        case 6: _t->sendMessage(); break;
        case 7: _t->clearChat(); break;
        case 8: { QString _r = _t->getCurrentTime();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *CatUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CatUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCatUIENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CatUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
