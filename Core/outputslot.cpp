#include "outputslot.h"



void NF::OutputSlot::setConnection(NF::Connection *connection)
{
    m_connections.push_back(connection);
}

void NF::OutputSlot::removeConnection(NF::Connection *connection)
{
    for (size_t i = 0; i < m_connections.size(); i++){
        if (connection == m_connections[i]){
            m_connections.erase(m_connections.begin() + i);
            return;
        }
    }
}
