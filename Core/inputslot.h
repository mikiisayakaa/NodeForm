#pragma once

/* Some features of an input slot:
 * 1.Can only link to one output slot (one connection)
 * 2.Have a default value, if there is no connection, the default value takes effect
 *  note that default value can be changed (e.g. using sliders to modify a float)
*/

#include "abstractslot.h"
#include "connection.h"
#include "outputslot.h"
#include "Wrapper/abstractslotsetter.h"
#include "Interface/abstractslotobject.h"
#include "Utils/debugutils.h"

namespace Nodest{

class Connection;
class AbstractSlotSetter;
class AbstractSlotObject;

class InputSlot : public AbstractSlot
{
public:

    template<typename T>
    T* getPointer(){
        if (!m_connection){
            return m_var->getPointer<T>();
        }
        else{
            return m_connection->getFirst()->getPointer<T>();
        }
    }

    void setConnection(Connection* connection) {m_connection = connection;}
    void removeConnection(Connection* connection) {
        ND_ASSERT(connection == m_connection,
                  QString("Trying to Remove a Connection that does not exist!"));
        if (connection == m_connection){
            m_connection = nullptr;
        }
    }

    Connection* getConnection() const {return m_connection;}

    template<typename T>
    static InputSlot* createSlot(const T& value){
        InputSlot* in = new InputSlot(value);
        return in;
    }

    /* WARNING: the owner of this class is responsible
     * to call this before deleting this
    */
    template<typename T>
    void destruct(){
        m_var->destruct<T>();
        delete m_setter;
        delete m_slotObject;
    }

    void setSetter(AbstractSlotSetter* setter) {m_setter = setter;}
    AbstractSlotSetter* getSetter() const {return m_setter;}

private:
    template <typename T>
    explicit InputSlot(const T& value)
        : AbstractSlot(value), m_connection(nullptr), m_setter(nullptr)
    {m_flow = 0;}

private:
    Connection* m_connection;

    AbstractSlotSetter* m_setter;

};

}

