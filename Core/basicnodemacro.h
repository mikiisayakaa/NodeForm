#pragma once

#include "Core/abstractevalnode.h"

#include <QHash>
#include <QDebug>

namespace NF{

static int nodeIDValue = 0;

template<typename NodeType>
class EvalNodeImpl : public AbstractEvalNode{

public:
    static AbstractNode* createInstance() { return new NodeType();}

protected:
    static const int NODE_ID;

protected:
    EvalNodeImpl() {}
};

typedef AbstractNode* (*CreateFuncType)();
struct NodeMetaData{
    int nodeID;
    QString nodeName;
    CreateFuncType createFunc;
};

QHash<int, NodeMetaData>& nodeIDToMetaData();
QHash<QString, int>&  nodeNameToID();

class GlobalNodeFactory{

public:
    static int registerNode(int id, const QString& nodeName, CreateFuncType func){
        qDebug() << id << nodeName;
        NodeMetaData metaData;
        metaData.nodeID = id;
        metaData.nodeName = nodeName;
        metaData.createFunc = func;
        nodeIDToMetaData().insert(id, metaData);
        nodeNameToID().insert(nodeName, id);
        return id;
    }

    static AbstractNode* createNode(int id){
        return nodeIDToMetaData()[id].createFunc();
    }

    static QString getNodeNameFromID(int id){
        return nodeIDToMetaData()[id].nodeName;
    }

    static AbstractNode* createNode(const QString& name){
        int id = nodeNameToID()[name];
        return createNode(id);
    }

    static int getNodeNum(){
        return nodeIDToMetaData().size();
    }

};


#ifndef BASICNODE
#define BASICNODE(nodeName, funcName) \
    class nodeName : public EvalNodeImpl<nodeName>{ \
    public: \
        using FuncType = decltype (&funcName); \
        using TP = NF::TupleTypes<FuncType>; \
        using InArgsType = TP::InputArgumentTypes; \
         \
        nodeName(const nodeName& node) = delete; \
        nodeName() : EvalNodeImpl<nodeName>(), m_func(funcName){ \
            m_nodeNameID = QString(#nodeName); \
            constructImpl<FuncType>(); \
        } \
         \
        ~nodeName(){ \
            destruct<FuncType>(); \
        } \
        nodeName* clone() const { \
            nodeName* newNode = new nodeName(); \
            return newNode; \
        } \
         \
        void eval(){ \
            evalImpl<FuncType>(m_func); \
            m_nodeObject->reEvaled(); \
        } \
         \
        void setValue(int slotIndex, void* ptr){ \
            setValueImpl<FuncType>(slotIndex, ptr); \
        } \
         \
    private: \
        FuncType m_func; \
    }; \
    \
    template <> \
    const int EvalNodeImpl<nodeName>::NODE_ID = GlobalNodeFactory::registerNode( \
         nodeIDValue++, QString(#nodeName), \
        &EvalNodeImpl<nodeName>::createInstance); \

#endif


}

