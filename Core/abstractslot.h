#pragma once

#include <QMetaType>
#include <QString>

#include "Utils/debugutils.h"
#include "Utils/variant.h"

#include <vector>

//a single slot
//NOTE: once a slot is created, its QVariant's type is determined
//      and cannot be changed during the slot's lifetime.

namespace Nodest{

class AbstractNode;
class Connection;
class AbstractSlotObject;

class AbstractSlot
{

public:
    template<typename T>
    explicit AbstractSlot(const T& value)
        : m_var(createVariant<T>(value)), m_typename(TYPENAME<T>::getName()) {}

    virtual ~AbstractSlot() {}

    template<typename T>
    void set(const T& value){
        m_var->set<T>(value);
    }

    template<typename T>
    void setPointer(void* ptr){
        m_var->setPointer<T>(ptr);
    }

    virtual void setConnection(Connection* connection) = 0;
    virtual void removeConnection(Connection* connection) = 0;

    void setParent(AbstractNode* parent) {m_parent = parent;}
    void setIndex(int index) {m_index = index;}
    int getIndex() const {return m_index;}
    int getFlow() const {return m_flow;}
    AbstractNode* getParent() const {return m_parent;}
    int getTypeID() const {return m_var->getTypeId();}
    QString getTypeName() const{return m_typename;}
    void setObj(AbstractSlotObject* slotObj) {m_slotObject = slotObj;}
    AbstractSlotObject* getObj() const {return m_slotObject;}

protected:
    AbstractNode* m_parent;

    //data here
    Variant* m_var;

    //flow = 0 for inputslot, flow = 1 for outputslot
    int m_flow;
    int m_index;

    QString m_typename;

    AbstractSlotObject* m_slotObject;

};

}

