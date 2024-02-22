#pragma once

#include <QObject>

#include "abstractslotsetter.h"
#include "Core/inputslot.h"

//send Q_OBJECT at qobj to fool moc, or it will not look into macros
#ifndef REGISTER_SLOT_SETTER
#define REGISTER_SLOT_SETTER(qobj, qinvoke, setterName, typeName) \
    class setterName : public AbstractSlotSetter \
    {\
        qobj \
    public: \
        explicit setterName(QObject* parent = nullptr) : AbstractSlotSetter(parent) { \
            m_typeName = TYPENAME<typeName>::getName(); \
        } \
        \
    public slots: \
        qinvoke void receiveValue(const typeName& value){ \
            m_slot->set<typeName>(value); \
            if (m_slot->getConnection() == nullptr){ \
                emit updated(); \
            } \
        } \
    };\
      \
    template <> \
    struct SetterTypeMapper<typeName> { \
        using Type = setterName; \
        using QMLType = typeName; \
        static Type* createInstance() { \
            return new Type(nullptr); \
        } \
    }; \

#endif

//user need to provide a convert function: typeName1 func(typeName2),
//typeName2 should be a QML type
#ifndef REGISTER_SLOT_SETTER_CONVERT
#define REGISTER_SLOT_SETTER_CONVERT(qobj, qinvoke, setterName, typeName1, typeName2, convertFunc) \
    class setterName : public AbstractSlotSetter \
    {\
        qobj \
    public: \
        explicit setterName(QObject* parent = nullptr) : AbstractSlotSetter(parent) { \
            m_typeName = TYPENAME<typeName2>::getName(); \
        } \
        \
    public slots: \
        qinvoke void receiveValue(const typeName2& value){ \
            typeName1 data = convertFunc(value); \
            m_slot->set<typeName1>(data); \
            emit updated(); \
        } \
    };\
      \
    template <> \
    struct SetterTypeMapper<typeName1> { \
        using Type = setterName; \
        using QMLType = typeName2; \
        static Type* createInstance() { \
            return new Type(nullptr); \
        } \
    }; \

#endif

namespace Nodest{
//raw TyepMapper should not be called,
//no AbstractSlotSetter type will be "int",
//no QMLType is "float" (QML does not support float)
template<typename T>
struct SetterTypeMapper {using Type = int;
                   using QMLType = float;
                   static AbstractSlotSetter* createInstance() {return nullptr;}};
}

