#include "abstractgraphobject.h"
#include "Extension/abstractextension.h"
#include "abstractconnectionobject.h"
#include "connectionobject.h"

Nodest::AbstractGraphObject::AbstractGraphObject(Nodest::AbstractNodeGraph *graph, QObject *parent)
    :  QObject(parent), m_graph(graph)
{
    graph->setObj(this);
}

Nodest::AbstractGraphObject::~AbstractGraphObject()
{
    while(m_nodeObjects.size() != 0){
        removeNodeObject(m_nodeObjects.front());
    }

    delete m_graph;
}

void Nodest::AbstractGraphObject::addNodeObject(Nodest::AbstractNodeObject *nodeObj)
{
    m_nodeObjects.push_back(nodeObj);

    m_graph->addNode(nodeObj->getNode());
    nodeObj->setParent(this);
}

void Nodest::AbstractGraphObject::reEvalSingle(Nodest::AbstractNodeObject *nodeObj)
{
    m_graph->reEvalSingle(nodeObj->getNode());
}

Nodest::AbstractConnectionObject *Nodest::AbstractGraphObject::addSingleConnection(Nodest::TestConnection *testConnection)
{
    Connection* connection = m_graph->addSingleConnection(testConnection);
    if (connection == nullptr){
        return nullptr;
    }

    ConnectionObject* connectObj = new ConnectionObject(this);
    connectObj->setConnection(connection);
    connection->setObj(connectObj);

    m_connectionObjects.push_back(connectObj);

    return connectObj;
}

void Nodest::AbstractGraphObject::removeNodeObject(Nodest::AbstractNodeObject *nodeObj)
{
    for (size_t i = 0; i < m_nodeObjects.size(); i++){
        if (m_nodeObjects[i] == nodeObj){
            m_nodeObjects.erase(m_nodeObjects.begin() + i);
            break;
        }
    }

    std::vector<AbstractConnectionObject*> deleteList;
    for (size_t i = 0; i < m_connectionObjects.size(); ){
        if (m_connectionObjects[i]->getConnection()->getFirst()->getParent()->getObj() == nodeObj ||
                m_connectionObjects[i]->getConnection()->getSecond()->getParent()->getObj() == nodeObj){
            deleteList.push_back(m_connectionObjects[i]);
            m_connectionObjects.erase(m_connectionObjects.begin() + i);
        }
        else{
            i++;
        }
    }
    m_graph->removeNode(nodeObj->getNode());

    delete nodeObj;
    for (size_t i = 0; i < deleteList.size(); i++){
        delete deleteList[i];
    }
}

void Nodest::AbstractGraphObject::removeSingleConnection(AbstractConnectionObject *connectionObject)
{
    for (size_t i = 0; i < m_connectionObjects.size(); i++){
        if (m_connectionObjects[i] == connectionObject){
            m_connectionObjects.erase(m_connectionObjects.begin() + i);
            break;
        }
    }

    m_graph->removeSingleConnection(connectionObject->getConnection());

    delete connectionObject;
}

void Nodest::AbstractGraphObject::copyNodeObj(Nodest::AbstractNodeObject *nodeObj)
{
    AbstractNodeObject* nodeObjCopy = nodeObj->clone();
    addNodeObject(nodeObjCopy);
}

void Nodest::AbstractGraphObject::addExtension(Nodest::AbstractExtension *extension)
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


