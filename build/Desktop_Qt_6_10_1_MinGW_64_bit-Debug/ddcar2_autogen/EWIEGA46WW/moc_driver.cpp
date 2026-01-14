/****************************************************************************
** Meta object code from reading C++ file 'driver.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../driver.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'driver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
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
struct qt_meta_tag_ZN6DriverE_t {};
} // unnamed namespace

template <> constexpr inline auto Driver::qt_create_metaobjectdata<qt_meta_tag_ZN6DriverE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Driver",
        "orderaccepted",
        "",
        "Order*",
        "order",
        "orderrejected",
        "tripstarted",
        "trippaused",
        "tripended",
        "locationupdated",
        "x",
        "y",
        "onlinestatuschanged",
        "online"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'orderaccepted'
        QtMocHelpers::SignalData<void(Order *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'orderrejected'
        QtMocHelpers::SignalData<void(Order *)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'tripstarted'
        QtMocHelpers::SignalData<void(Order *)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'trippaused'
        QtMocHelpers::SignalData<void(Order *)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'tripended'
        QtMocHelpers::SignalData<void(Order *)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'locationupdated'
        QtMocHelpers::SignalData<void(int, int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 }, { QMetaType::Int, 11 },
        }}),
        // Signal 'onlinestatuschanged'
        QtMocHelpers::SignalData<void(bool)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 13 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Driver, qt_meta_tag_ZN6DriverE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Driver::staticMetaObject = { {
    QMetaObject::SuperData::link<User::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6DriverE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6DriverE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6DriverE_t>.metaTypes,
    nullptr
} };

void Driver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Driver *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->orderaccepted((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1]))); break;
        case 1: _t->orderrejected((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1]))); break;
        case 2: _t->tripstarted((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1]))); break;
        case 3: _t->trippaused((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1]))); break;
        case 4: _t->tripended((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1]))); break;
        case 5: _t->locationupdated((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->onlinestatuschanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Driver::*)(Order * )>(_a, &Driver::orderaccepted, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Driver::*)(Order * )>(_a, &Driver::orderrejected, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Driver::*)(Order * )>(_a, &Driver::tripstarted, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Driver::*)(Order * )>(_a, &Driver::trippaused, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Driver::*)(Order * )>(_a, &Driver::tripended, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Driver::*)(int , int )>(_a, &Driver::locationupdated, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Driver::*)(bool )>(_a, &Driver::onlinestatuschanged, 6))
            return;
    }
}

const QMetaObject *Driver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Driver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6DriverE_t>.strings))
        return static_cast<void*>(this);
    return User::qt_metacast(_clname);
}

int Driver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = User::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Driver::orderaccepted(Order * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Driver::orderrejected(Order * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Driver::tripstarted(Order * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Driver::trippaused(Order * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Driver::tripended(Order * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void Driver::locationupdated(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void Driver::onlinestatuschanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}
QT_WARNING_POP
