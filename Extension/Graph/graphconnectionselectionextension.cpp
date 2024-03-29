#include "graphconnectionselectionextension.h"
#include "Interface/abstractconnectionobject.h"
#include "Interface/abstractgraphobject.h"
#include "Extension/Graph/graphnodeselectionextension.h"

bool NF::GraphConnectionSelectionExtension::addExtension(QQuickItem *signalSource)
{
    connect(signalSource, SIGNAL(deselect()), this, SLOT(onDeselect()));
    return true;
}

void NF::GraphConnectionSelectionExtension::selectOne(NF::AbstractConnectionObject *connectObj)
{
    for (auto selectedObj : m_selectedConnections){
        if (selectedObj == connectObj){
            return;
        }
    }

    connectObj->getItem()->setProperty("selected", true);
    m_selectedConnections.push_back(connectObj);

    //interaction with node selection Extension
    AbstractGraphObject* graphObj = dynamic_cast<AbstractGraphObject*>(parent());
    std::vector<AbstractExtension*> siblingExtensions = graphObj->getExtensions();

    for (size_t i = 0; i < siblingExtensions.size(); i++){
        if (siblingExtensions[i]->getExtensionType() == ExtensionType::GraphNodeSelection){
            GraphNodeSelectionExtension* nodeSelectionExtension =
                    dynamic_cast<GraphNodeSelectionExtension*>(siblingExtensions[i]);
            nodeSelectionExtension->onDeselect();
        }
    }
}

void NF::GraphConnectionSelectionExtension::deselectOne(NF::AbstractConnectionObject *connectObj)
{
    for (size_t i = 0; i < m_selectedConnections.size(); i++){
        if (m_selectedConnections[i] == connectObj){
            connectObj->getItem()->setProperty("selected", false);
            m_selectedConnections.erase(m_selectedConnections.begin() + i);
            break;
        }
    }
}

void NF::GraphConnectionSelectionExtension::onDeselect()
{
    for (auto connectObj : m_selectedConnections){
        connectObj->getItem()->setProperty("selected", false);
    }

    m_selectedConnections.clear();

}


