#include "graphnodeselectionextension.h"
#include "Extension/Graph/graphconnectionselectionextension.h"
#include "Interface/abstractnodeobject.h"
#include "Interface/abstractgraphobject.h"

bool Nodest::GraphNodeSelectionExtension::addExtension(QQuickItem *signalSource)
{
    connect(signalSource, SIGNAL(deselect()), this, SLOT(onDeselect()));
    return true;
}

void Nodest::GraphNodeSelectionExtension::selectOne(Nodest::AbstractNodeObject *nodeObj)
{
    for (auto selectedObj : m_selectedNodes){
        if (selectedObj == nodeObj){
            return;
        }
    }

    nodeObj->getNodeBase()->setProperty("selected", true);
    m_selectedNodes.push_back(nodeObj);

    //interact with connection selection Extension

    AbstractGraphObject* graphObj = dynamic_cast<AbstractGraphObject*>(parent());
    std::vector<AbstractExtension*> siblingExtensions = graphObj->getExtensions();

    for (size_t i = 0; i < siblingExtensions.size(); i++){
        if (siblingExtensions[i]->getExtensionName() == "GraphConnectionSelection"){
            GraphConnectionSelectionExtension* connectionSelectionExtension =
                    dynamic_cast<GraphConnectionSelectionExtension*>(siblingExtensions[i]);
            connectionSelectionExtension->onDeselect();
        }
    }
}

void Nodest::GraphNodeSelectionExtension::deselectOne(Nodest::AbstractNodeObject *nodeObj)
{
    for (size_t i = 0; i < m_selectedNodes.size(); i++){
        if (m_selectedNodes[i] == nodeObj){
            nodeObj->getNodeBase()->setProperty("selected", false);
            m_selectedNodes.erase(m_selectedNodes.begin() + i);
            break;
        }
    }

}

void Nodest::GraphNodeSelectionExtension::onDeselect()
{
    for (auto nodeObj : m_selectedNodes){
        nodeObj->getNodeBase()->setProperty("selected", false);
    }

    m_selectedNodes.clear();
}
