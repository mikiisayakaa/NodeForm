#include "abstractnodegraph.h"

#include <QDebug>

NF::AbstractNodeGraph::~AbstractNodeGraph()
{
    for (size_t i = 0; i < m_connections.size(); i++){
        delete m_connections[i];
    }

    for (size_t i = 0; i < m_nodes.size(); i++){
        delete m_nodes[i];
    }

    delete m_graphObject;
}

void NF::AbstractNodeGraph::addNodeToList(NF::AbstractNode *node)
{
    m_nodes.push_back(node);
}

void NF::AbstractNodeGraph::removeNodeFromList(NF::AbstractNode *node)
{
    for (size_t i = 0; i < m_nodes.size(); i++){
        if (m_nodes[i] == node){
            m_nodes.erase(m_nodes.begin() + i);
            return;
        }
    }
}

void NF::AbstractNodeGraph::addConnectionToList(NF::Connection *connection)
{
    m_connections.push_back(connection);
}

void NF::AbstractNodeGraph::removeConnectionFromList(NF::Connection *connection)
{
    for (size_t i = 0; i < m_connections.size(); i++){
        if (m_connections[i] == connection){
            m_connections.erase(m_connections.begin() + i);
            return;
        }
    }
}
