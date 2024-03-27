#pragma once

#include "abstractdatabridge.h"
#include "abstractnodeobject.h"
#include "abstractgraphobject.h"
#include "Core/inputslot.h"
#include "Core/outputslot.h"

#include <iostream>

namespace NF{

static int bridgeIDValue = 0;

template<typename BridgeType>
class DataBridgeImpl : public AbstractDataBridge{

public:
    static AbstractDataBridge* createInstance() { return new BridgeType(nullptr);}

protected:
    static const int BRIDGE_ID;

protected:
    DataBridgeImpl() {}
};

typedef AbstractDataBridge* (*CreateBridgeFuncType)();
struct BridgeMetaData{
    int bridgeID;
    QString cppType;
    QString qmlType;
    CreateBridgeFuncType createFunc;
};

class BridgeTypes{
public:
    QString cppType;
    QString qmlType;

    friend uint qHash(const BridgeTypes& key){
        uint hash = 0;
        hash ^= qHash(key.cppType + key.qmlType);
        return hash;
    }

    friend bool operator==(const BridgeTypes &lhs, const BridgeTypes &rhs)
    {
        return lhs.cppType == rhs.cppType && lhs.qmlType == rhs.qmlType;
    }
};

QHash<int, BridgeMetaData>& bridgeIDToMetaData();
QHash<BridgeTypes, int>&  bridgeTypesToID();



class GlobalBridgeFactory{

public:
    static int registerBridge(int id, const QString& cppType, const QString& qmlType,
                              CreateBridgeFuncType func){
        qDebug() << id << cppType << qmlType;
        BridgeMetaData metaData;
        metaData.bridgeID = id;
        metaData.cppType = cppType;
        metaData.qmlType = qmlType;
        metaData.createFunc = func;
        bridgeIDToMetaData().insert(id, metaData);
        bridgeTypesToID().insert({cppType, qmlType}, id);
        return id;
    }

    static AbstractDataBridge* createBridge(int id){
        return bridgeIDToMetaData()[id].createFunc();
    }

    static BridgeTypes getBridgeTypesFromID(int id){
        return {bridgeIDToMetaData()[id].cppType, bridgeIDToMetaData()[id].qmlType};
    }

    static AbstractDataBridge* createBridge(const QString& cppType, const QString& qmlType){
        int id = bridgeTypesToID()[{cppType, qmlType}];
        return createBridge(id);
    }

    static int getBridgeNum(){
        return bridgeIDToMetaData().size();
    }

};


//send Q_OBJECT at qobj to fool moc, or it will not look into macros
#ifndef REGISTER_DATABRIDGE
#define REGISTER_DATABRIDGE(qobj, qinvoke, bridgeName, typeName) \
    class bridgeName : public AbstractDataBridge \
    {\
        qobj \
    public: \
        explicit bridgeName(QObject* parent = nullptr) : AbstractDataBridge(parent) { \
        } \
        \
        void bind(){ \
            if (m_slot->getFlow() == 0) { \
                connect(m_item, (QString("2qmlData(") + QString(#typeName) + QString(")")).toStdString().c_str(), \
                        this, (QString("1receiveValue(") + QString(#typeName) + QString(")")).toStdString().c_str()); \
            } \
            else { \
                AbstractNodeObject* nodeObj = dynamic_cast<AbstractNodeObject*>(parent()->parent()); \
                connect(nodeObj, (QString("2reEvaled()")).toStdString().c_str(), this, \
                        (QString("1sendValue()")).toStdString().c_str()); \
            } \
        } \
    public slots: \
        qinvoke void receiveValue(const typeName& value){ \
            m_slot->set<typeName>(value); \
            if (((InputSlot*)m_slot)->getConnection() == nullptr){ \
                AbstractNodeObject* nodeObj = dynamic_cast<AbstractNodeObject*>(parent()->parent()); \
                AbstractGraphObject* graphObj = dynamic_cast<AbstractGraphObject*>(nodeObj->parent()); \
                graphObj->reEvalSingle(nodeObj); \
            } \
        } \
        qinvoke void sendValue(){ \
            typeName* ptr; \
            if (m_slot->getFlow() == 0) { \
                ptr = ((InputSlot*)m_slot)->getPointer<typeName>(); \
            } \
            else { \
                ptr = ((OutputSlot*)m_slot)->getPointer<typeName>(); \
            } \
            m_item->setProperty("cppData", *ptr); \
        } \
    };\
      \
    template <> \
    const int DataBridgeImpl<bridgeName>::BRIDGE_ID = GlobalBridgeFactory::registerBridge( \
         bridgeIDValue++, QString(#typeName), QString(#typeName), \
        &DataBridgeImpl<bridgeName>::createInstance); \

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
        void bind(){ \
            if (m_slot->getFlow() == 0) { \
                connect(m_item, (QString("2qmlData(") + QString(#qmlType) + QString(")")).toStdString().c_str(), \
                        this, (QString("1receiveValue(") + QString(#qmlType) + QString(")")).toStdString().c_str()); \
            } \
            else { \
                AbstractNodeObject* nodeObj = dynamic_cast<AbstractNodeObject*>(parent()->parent()); \
                connect(nodeObj, (QString("2reEvaled()")).toStdString().c_str(), this, \
                        (QString("1sendValue()")).toStdString().c_str()); \
            } \
        } \
    public slots: \
        qinvoke void receiveValue(const qmlType& value){ \
            m_slot->set<cppType>(QmlToCpp(value)); \
            if (((InputSlot*)m_slot)->getConnection() == nullptr){ \
                AbstractNodeObject* nodeObj = dynamic_cast<AbstractNodeObject*>(parent()->parent()); \
                AbstractGraphObject* graphObj = dynamic_cast<AbstractGraphObject*>(nodeObj->parent()); \
                graphObj->reEvalSingle(nodeObj); \
            } \
        } \
        qinvoke void sendValue(){ \
            cppType* ptr; \
            if (m_slot->getFlow() == 0) { \
                ptr = ((InputSlot*)m_slot)->getPointer<cppType>(); \
            } \
            else { \
                ptr = ((OutputSlot*)m_slot)->getPointer<cppType>(); \
            } \
            qmlType data = cppToQml(*ptr); \
            m_item->setProperty("cppData", data); \
        } \
    };\
      \
    template <> \
    const int DataBridgeImpl<bridgeName>::BRIDGE_ID = GlobalBridgeFactory::registerBridge( \
         bridgeIDValue++, QString(#cppType), QString(#qmlType), \
        &DataBridgeImpl<bridgeName>::createInstance); \

#endif

}
