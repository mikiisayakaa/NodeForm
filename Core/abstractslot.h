#pragma once

#include <QString>

#include "Utils/variant.h"

/* a single slot
 * NOTE: once a slot is created, its Variant's type is determined
 *      and cannot be changed during the slot's lifetime.
*/

namespace NF{

class AbstractNode;
class Connection;
class AbstractSlotObject;

class AbstractSlot
{

public:

    template<typename T>
    explicit AbstractSlot(const T& value)
        : m_var(Variant::createVariant<T>(value)) {}

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
    AbstractNode* getParent() const {return m_parent;}

    void setIndex(int index) {m_index = index;}
    int getIndex() const {return m_index;}

    int getFlow() const {return m_flow;} 

    int getTypeID() const {return m_var->getTypeId();}

    QString getTypeName() const {return m_var->getTypeName();}

    void setObj(AbstractSlotObject* slotObj) {m_slotObject = slotObj;}
    AbstractSlotObject* getObj() const {return m_slotObject;}

protected:
    AbstractNode* m_parent;

    // slot data here
    Variant* m_var;

    /* flow = 0 for inputslot, flow = 1 for outputslot.
     * We don't use enum classes here, because the need to communicate with qml.
    */
    int m_flow;

    // index of this slot in the node
    int m_index;

    AbstractSlotObject* m_slotObject;

};

}

