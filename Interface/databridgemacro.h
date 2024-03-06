#pragma once

#include "abstractdatabridge.h"

//send Q_OBJECT at qobj to fool moc, or it will not look into macros
#ifndef REGISTER_DATABRIDGE
#define REGISTER_DATABRIDGE(qobj, qinvoke, bridgeName, typeName) \
    class bridgeName : public AbstractDataBridge \
    {\
        qobj \
    public: \
        explicit bridgeName(QObject* parent = nullptr) : AbstractDataBridge(parent) { \
            \
        } \
        \
        void sendValue(){ \
            typeName* ptr = m_slot->getPointer<typeName>(); \
            m_item->setProperty("cppData", *ptr); \
        } \
        \
    signals: \
        void updated(); \
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
    struct BridgeTypeMapper<typeName, typeName> { \
        using Type = bridgeName; \
        using QMLType = typeName; \
        using CppType = typeName; \
        static Type* createInstance() { \
            return new Type(nullptr); \
        } \
    }; \

#endif

//user need to provide a convert function: typeName2 func(typeName1),
//typeName2 should be a QML type
#ifndef REGISTER_DATABRIDGE_CONVERT
#define REGISTER_DATABRIDGE_CONVERT(qobj, qinvoke, bridgeName, cppType, qmlType, cppToQml, QmlToCpp) \
    class bridgeName : public AbstractDataBridge \
    {\
        qobj \
    public: \
        explicit bridgeName(QObject* parent = nullptr) : AbstractDataBridge(parent) { \
             \
        } \
        \
        void sendValue(){ \
            qmlType data = cppToQml(*(m_slot->getPointer<cppType>())); \
            m_item->setProperty("cppData", data); \
        } \
        \
    signals: \
        void updated(); \
    public slots: \
        qinvoke void receiveValue(const qmlType& value){ \
            m_slot->set<typeName>(qmlToCpp(value)); \
            if (m_slot->getConnection() == nullptr){ \
                emit updated(); \
            } \
        } \
    };\
      \
    template <> \
    struct BridgeTypeMapper<cppType, qmlType> { \
        using Type = bridgeName; \
        using CppType = cppType; \
        using QMLType = qmlType; \
        static Type* createInstance() { \
            return new Type(nullptr); \
        } \
    }; \

#endif

namespace NF{
template<typename cpp, typename qml>
struct BridgeTypeMapper {using Type = int;
                   using cppType = int;
                   using QMLType = int;
                   static AbstractDataBridge* createInstance() {return nullptr;}};
}
