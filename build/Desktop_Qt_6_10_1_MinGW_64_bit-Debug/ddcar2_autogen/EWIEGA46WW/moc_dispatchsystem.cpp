/****************************************************************************
** Meta object code from reading C++ file 'dispatchsystem.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../dispatchsystem.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dispatchsystem.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14DispatchSystemE_t {};
} // unnamed namespace

template <> constexpr inline auto DispatchSystem::qt_create_metaobjectdata<qt_meta_tag_ZN14DispatchSystemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DispatchSystem",
        "driverassigned",
        "",
        "Order*",
        "order",
        "Driver*",
        "driver",
        "nodriveravailable",
        "availableordersupdated",
        "orderacceptedbyother",
        "ondriverstatuschanged",
        "ondriveronlinestatuschanged",
        "online",
        "onorderstatuschanged",
        "oldstatus",
        "newstatus"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'driverassigned'
        QtMocHelpers::SignalData<void(Order *, Driver *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Signal 'nodriveravailable'
        QtMocHelpers::SignalData<void(Order *)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'availableordersupdated'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'orderacceptedbyother'
        QtMocHelpers::SignalData<void(Order *)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'ondriverstatuschanged'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'ondriveronlinestatuschanged'
        QtMocHelpers::SlotData<void(bool)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 12 },
        }}),
        // Slot 'onorderstatuschanged'
        QtMocHelpers::SlotData<void(Order *, int, int)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::Int, 14 }, { QMetaType::Int, 15 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DispatchSystem, qt_meta_tag_ZN14DispatchSystemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DispatchSystem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14DispatchSystemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14DispatchSystemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14DispatchSystemE_t>.metaTypes,
    nullptr
} };

void DispatchSystem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DispatchSystem *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->driverassigned((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Driver*>>(_a[2]))); break;
        case 1: _t->nodriveravailable((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1]))); break;
        case 2: _t->availableordersupdated(); break;
        case 3: _t->orderacceptedbyother((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1]))); break;
        case 4: _t->ondriverstatuschanged(); break;
        case 5: _t->ondriveronlinestatuschanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->onorderstatuschanged((*reinterpret_cast<std::add_pointer_t<Order*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DispatchSystem::*)(Order * , Driver * )>(_a, &DispatchSystem::driverassigned, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DispatchSystem::*)(Order * )>(_a, &DispatchSystem::nodriveravailable, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (DispatchSystem::*)()>(_a, &DispatchSystem::availableordersupdated, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (DispatchSystem::*)(Order * )>(_a, &DispatchSystem::orderacceptedbyother, 3))
            return;
    }
}

const QMetaObject *DispatchSystem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DispatchSystem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14DispatchSystemE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DispatchSystem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void DispatchSystem::driverassigned(Order * _t1, Driver * _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void DispatchSystem::nodriveravailable(Order * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void DispatchSystem::availableordersupdated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DispatchSystem::orderacceptedbyother(Order * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}
QT_WARNING_POP
