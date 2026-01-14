/****************************************************************************
** Meta object code from reading C++ file 'ordermanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../ordermanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ordermanager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12OrderManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto OrderManager::qt_create_metaobjectdata<qt_meta_tag_ZN12OrderManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "OrderManager",
        "ordercreated",
        "",
        "Order*",
        "order",
        "orderstatuschanged",
        "Order::Status",
        "oldStatus",
        "newStatus",
        "orderassigned",
        "Driver*",
        "driver",
        "ordercancelled",
        "ordercompleted"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'ordercreated'
        QtMocHelpers::SignalData<void(Order *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'orderstatuschanged'
        QtMocHelpers::SignalData<void(Order *, Order::Status, Order::Status)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 6, 7 }, { 0x80000000 | 6, 8 },
        }}),
        // Signal 'orderassigned'
        QtMocHelpers::SignalData<void(Order *, Driver *)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 10, 11 },
        }}),
        // Signal 'ordercancelled'
        QtMocHelpers::SignalData<void(Order *)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'ordercompleted'
        QtMocHelpers::SignalData<void(Order *)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<OrderManager, qt_meta_tag_ZN12OrderManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject OrderManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12OrderManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12OrderManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12OrderManagerE_t>.metaTypes,
    nullptr
} };

void OrderManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<OrderManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->ordercreated((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1]))); break;
        case 1: _t->orderstatuschanged((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Order::Status>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<Order::Status>>(_a[3]))); break;
        case 2: _t->orderassigned((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Driver*>>(_a[2]))); break;
        case 3: _t->ordercancelled((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1]))); break;
        case 4: _t->ordercompleted((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Order* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Order* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Order* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Order* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Order* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (OrderManager::*)(Order * )>(_a, &OrderManager::ordercreated, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (OrderManager::*)(Order * , Order::Status , Order::Status )>(_a, &OrderManager::orderstatuschanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (OrderManager::*)(Order * , Driver * )>(_a, &OrderManager::orderassigned, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (OrderManager::*)(Order * )>(_a, &OrderManager::ordercancelled, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (OrderManager::*)(Order * )>(_a, &OrderManager::ordercompleted, 4))
            return;
    }
}

const QMetaObject *OrderManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OrderManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12OrderManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int OrderManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void OrderManager::ordercreated(Order * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void OrderManager::orderstatuschanged(Order * _t1, Order::Status _t2, Order::Status _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3);
}

// SIGNAL 2
void OrderManager::orderassigned(Order * _t1, Driver * _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void OrderManager::ordercancelled(Order * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void OrderManager::ordercompleted(Order * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}
QT_WARNING_POP
