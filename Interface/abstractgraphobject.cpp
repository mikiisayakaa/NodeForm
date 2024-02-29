#include "abstractgraphobject.h"
#include "Extension/abstractextension.h"

Nodest::AbstractGraphObject::AbstractGraphObject(Nodest::AbstractNodeGraph *graph, QObject *parent)
    :  QObject(parent), m_graph(graph)
{
    graph->setObj(this);
}

Nodest::AbstractGraphObject::~AbstractGraphObject()
{
    for (size_t i = 0; i < m_nodeObjects.size(); i++){
        m_graph->removeNode(m_nodeObjects[i]->getNode());
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

Nodest::Connection *Nodest::AbstractGraphObject::addSingleConnection(Nodest::TestConnection *testConnection)
{
    return m_graph->addSingleConnection(testConnection);
}

void Nodest::AbstractGraphObject::removeNodeObject(Nodest::AbstractNodeObject *nodeObj)
{
    removeObjectFromVector(nodeObj);
    m_graph->removeNode(nodeObj->getNode());
}

void Nodest::AbstractGraphObject::removeSingleConnection(ConnectionObject *connectionObject)
{
    m_graph->removeSingleConnection(connectionObject->getConnection());
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


void Nodest::AbstractGraphObject::removeObjectFromVector(Nodest::AbstractNodeObject *nodeObj)
{
    for (size_t i = 0; i < m_nodeObjects.size(); i++){
        if (m_nodeObjects[i] == nodeObj){
            m_nodeObjects.erase(m_nodeObjects.begin() + i);
            break;
        }
    }
}

