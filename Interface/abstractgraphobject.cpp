#include "abstractgraphobject.h"
#include "Extension/abstractextension.h"
#include "abstractconnectionobject.h"
#include "connectionobject.h"

NF::AbstractGraphObject::AbstractGraphObject(NF::AbstractNodeGraph *graph, QObject *parent)
    :  QObject(parent), m_graph(graph)
{
    graph->setObj(this);
}


void NF::AbstractGraphObject::addNodeObject(NF::AbstractNodeObject *nodeObj)
{
    m_graph->addNode(nodeObj->getNode());
    nodeObj->setParent(this);
}

void NF::AbstractGraphObject::reEvalSingle(NF::AbstractNodeObject *nodeObj)
{
    m_graph->reEvalSingle(nodeObj->getNode());
}

NF::AbstractConnectionObject *NF::AbstractGraphObject::addSingleConnection(NF::TestConnection *testConnection)
{
    Connection* connection = m_graph->addSingleConnection(testConnection);
    if (connection == nullptr){
        return nullptr;
    }

    ConnectionObject* connectObj = new ConnectionObject(this);
    connectObj->setConnection(connection);
    connection->setObj(connectObj);

    return connectObj;
}

void NF::AbstractGraphObject::removeNodeObject(NF::AbstractNodeObject *nodeObj)
{
    m_graph->removeNode(nodeObj->getNode());
}

void NF::AbstractGraphObject::removeSingleConnection(AbstractConnectionObject *connectionObject)
{
    m_graph->removeSingleConnection(connectionObject->getConnection());
}

void NF::AbstractGraphObject::copyNodeObj(NF::AbstractNodeObject *nodeObj)
{
    AbstractNodeObject* nodeObjCopy = nodeObj->clone();
    addNodeObject(nodeObjCopy);
}

void NF::AbstractGraphObject::addExtension(NF::AbstractExtension *extension)
{
    for (size_t i = 0; i < m_extensions.size(); i++){
        if (m_extensions[i]->getExtensionType() == extension->getExtensionType()){
            return;
        }
    }


    if (extension->addExtension(m_background)){
        m_extensions.push_back(extension);
    }
    else{
        delete extension;
    }


}


