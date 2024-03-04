#pragma once

#include <QObject>

#include "abstractslotgetter.h"
#include "Core/outputslot.h"

#ifndef REGISTER_SLOT_GETTER
#define REGISTER_SLOT_GETTER(qobj, getterName, typeName) \
    class getterName : public AbstractSlotGetter \
    {\
        qobj \
    public: \
        explicit getterName(QObject* parent = nullptr) : AbstractSlotGetter(parent) { \
            m_typeName = TYPENAME<typeName>::getName(); \
        } \
        \
        void sendValue(){ \
            typeName* ptr = m_slot->getPointer<typeName>(); \
            m_item->setProperty("dataValue", *ptr); \
        } \
    };\
      \
    template <> \
    struct GetterTypeMapper<typeName> { \
        using Type = getterName; \
        using QMLType = typeName; \
        static Type* createInstance() { \
            return new Type(nullptr); \
        } \
    }; \

#endif

//user need to provide a convert function: typeName2 func(typeName1),
//typeName2 should be a QML type
#ifndef REGISTER_SLOT_GETTER_CONVERT
#define REGISTER_SLOT_GETTER_CONVERT(qobj, getterName, typeName1, typeName2, convertFunc) \
    class getterName : public AbstractSlotGetter \
    {\
        qobj \
    public: \
        explicit getterName(QObject* parent = nullptr) : AbstractSlotGetter(parent) { \
            m_typeName = TYPENAME<typeName1>::getName(); \
        } \
        \
        void sendValue(){ \
            typeName2 data = convertFunc(*(m_slot->getPointer<typeName1>())); \
            m_item->setProperty("dataValue", data); \
        } \
    };\
      \
    template <> \
    struct GetterTypeMapper<typeName1> { \
        using Type = getterName; \
        using QMLType = typeName2; \
        static Type* createInstance() { \
            return new Type(nullptr); \
        } \
    }; \

#endif

namespace NF{
template<typename T>
struct GetterTypeMapper {using Type = int;
                   using QMLType = float;
                   static AbstractSlotGetter* createInstance() {return nullptr;}};
}
