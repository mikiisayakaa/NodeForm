#include "deleteselectednodeextension.h"
#include "Interface/abstractgraphobject.h"
#include "Extension/Graph/graphnodeselectionextension.h"

bool Nodest::DeleteSelectedNodeExtension::addExtension(QQuickItem *signalSource)
{
    if (checkDependency()){
        connect(signalSource, SIGNAL(deleteSelected()), this, SLOT(onDelete()));
        return true;
    }

    return false;
}

bool Nodest::DeleteSelectedNodeExtension::checkDependency()
{
    AbstractGraphObject* graphObj = dynamic_cast<AbstractGraphObject*>(parent());
    std::vector<AbstractExtension*> parentExtensions = graphObj->getExtensions();
    for (size_t i = 0; i < parentExtensions.size(); i++){
        if (parentExtensions[i]->getExtensionType() == ExtensionType::GraphNodeSelection){
            m_graphSelectionExtension = dynamic_cast<GraphNodeSelectionExtension*>(parentExtensions[i]);
            return true;
        }
    }

    return false;
}

void Nodest::DeleteSelectedNodeExtension::onDelete()
{
    AbstractGraphObject* graphObject = dynamic_cast<AbstractGraphObject*>(parent());
    std::vector<AbstractNodeObject*>& selectedNodes = m_graphSelectionExtension->getSelectedNodes();

    for (auto& nodeObj : selectedNodes){
        graphObject->removeNodeObject(nodeObj);
    }

    selectedNodes.clear();
}
