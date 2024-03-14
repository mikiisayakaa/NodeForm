#pragma once

/* Some features of an input slot:
 * 1.Can only link to one output slot (one connection)
 * 2.Have a default value, if there is no connection, the default value takes effect
 *  note that default value can be changed (e.g. using sliders to modify a float)
*/

#include "abstractslot.h"
#include "connection.h"
#include "outputslot.h"
#include "Interface/abstractslotobject.h"
#include "Utils/debugutils.h"

namespace NF{

class Connection;
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
        NF_ASSERT(connection == m_connection,
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
        delete m_slotObject;
    }


private:
    template <typename T>
    explicit InputSlot(const T& value)
        : AbstractSlot(value), m_connection(nullptr)
    {m_flow = 0;}

private:
    Connection* m_connection;

};

}

