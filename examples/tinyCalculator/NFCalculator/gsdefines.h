#pragma once

#include "Wrapper/slotgettermacro.h"
#include "Wrapper/slotsettermacro.h"
#include "typedefines.h"
#include "Interface/databridgemacro.h"

namespace NF{

REGISTER_SLOT_SETTER(Q_OBJECT, Q_INVOKABLE, IntSetter, int)
REGISTER_SLOT_SETTER(Q_OBJECT, Q_INVOKABLE, DoubleSetter, double)

REGISTER_SLOT_GETTER(Q_OBJECT, IntGetter, int)

REGISTER_DATABRIDGE(Q_OBJECT, Q_INVOKABLE, IntToIntBridge, int)
REGISTER_DATABRIDGE(Q_OBJECT, Q_INVOKABLE, DoubleToDoubleBridge, double)

//class IntToIntBridge : public AbstractDataBridge
//{
//    Q_OBJECT
//public:
//    explicit IntToIntBridge(QObject* parent = nullptr) : AbstractDataBridge(parent) {
//    }

//private:
//    void bind(){
//        if (m_slot->getFlow() == 0) {
//            connect(m_item, (QString("2qmlData(") + QString("int") + QString(")")).toStdString().c_str(),
//                    this, (QString("1receiveValue(") + QString("int") + QString(")")).toStdString().c_str());
//        }
//    }
//public slots:
//    Q_INVOKABLE void receiveValue(const int& value){
//        m_slot->set<int>(value);
//        if (((InputSlot*)m_slot)->getConnection() == nullptr){
//            AbstractNodeObject* nodeObj = dynamic_cast<AbstractNodeObject*>(parent()->parent());
//            AbstractGraphObject* graphObj = dynamic_cast<AbstractGraphObject*>(nodeObj->parent());
//            graphObj->reEvalSingle(nodeObj);
//        }
//    }
//    void sendValue(){
//        int* ptr;
//        if (m_slot->getFlow() == 0) {
//            ptr = ((InputSlot*)m_slot)->getPointer<int>();
//        }
//        else {
//            ptr = ((OutputSlot*)m_slot)->getPointer<int>();
//        }
//        m_item->setProperty("cppData", *ptr);
//    }
//};

//template <>
//const int DataBridgeImpl<IntToIntBridge>::BRIDGE_ID = GlobalBridgeFactory::registerBridge(
//     bridgeIDValue++, QString("int"), QString("int"),
//    &DataBridgeImpl<IntToIntBridge>::createInstance);


}
