#pragma once

#include "Core/abstractevalnode.h"

#include <QHash>

namespace NF{

inline static QHash<QString, int> nodeMap;

#ifndef BASICNODE
#define BASICNODE(nodeName, funcName) \
    class nodeName : public NF::AbstractEvalNode{ \
    public: \
        using FuncType = decltype (&funcName); \
        using TP = NF::TupleTypes<FuncType>; \
        using InArgsType = TP::InputArgumentTypes; \
         \
        nodeName(const nodeName& node) = delete; \
        explicit nodeName() : NF::AbstractEvalNode(), m_func(funcName){ \
            m_nodeNameID = QString(#nodeName); \
            m_outValid = true; \
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
        } \
         \
        void setValue(int slotIndex, void* ptr){ \
            setValueImpl<FuncType>(slotIndex, ptr); \
        } \
        void bindSetter(QQuickItem* item, int index) { \
            bindInputSettersImpl<FuncType>(item, index); \
        } \
         \
    private: \
        FuncType m_func; \
    }; \
    \

#endif

}

