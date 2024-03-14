#pragma once

#include <vector>

#include "abstractslot.h"
#include "connection.h"
#include "inputslot.h"
#include "abstractnode.h"
#include "Interface/abstractslotobject.h"

namespace NF{

class Connection;
class AbstractSlotGetter;
class AbstractSlotObject;

class OutputSlot : public AbstractSlot
{
public:
    template<typename T>
    OutputSlot(const T& value) :AbstractSlot(value), m_getter(nullptr) {m_flow = 1;}

    template<typename T>
    T* getPointer(){
        return m_var->getPointer<T>();
    }

    int getNConnection() const {return m_connections.size();}
    Connection* getConnection(int index) const {return m_connections[index];}

    void setConnection(Connection* connection);
    void removeConnection(Connection* connection);

    template<typename T>
    void verbose(){
        qDebug() << "From Node:" << m_parent->getNameID();
        qDebug() << "OutputSlot type: [" << TYPENAME<T>::getName() << "], OutputSlot value: "
                 << get<T>();
    }

    template<typename T>
    static OutputSlot* createSlot(const T& value){
        OutputSlot* out = new OutputSlot(value);
        return out;
    }

    //WARNING: the owner of this class is responsible
    //to call this before delete
    template<typename T>
    void destruct(){
        m_var->destruct<T>();
        delete m_getter;
        delete m_slotObject;
    }

    void setGetter(AbstractSlotGetter* getter){m_getter = getter;}
    AbstractSlotGetter* getGetter() const {return m_getter;}

private:
    std::vector<Connection*> m_connections;

    AbstractSlotGetter* m_getter;
};



}

