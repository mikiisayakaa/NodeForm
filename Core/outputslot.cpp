#include "outputslot.h"



void Nodest::OutputSlot::setConnection(Nodest::Connection *connection)
{
    m_connections.push_back(connection);
}

void Nodest::OutputSlot::removeConnection(Nodest::Connection *connection)
{
    for (size_t i = 0; i < m_connections.size(); i++){
        if (connection == m_connections[i]){
            m_connections.erase(m_connections.begin() + i);
            return;
        }
    }
}
