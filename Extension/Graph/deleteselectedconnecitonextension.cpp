#include "deleteselectedconnecitonextension.h"
#include "Interface/abstractgraphobject.h"
#include "Interface/abstractconnectionobject.h"
#include "Extension/Graph/graphconnectionselectionextension.h"

bool Nodest::DeleteSelectedConnecitonExtension::addExtension(QQuickItem *signalSource)
{
    if (checkDependency()){
        connect(signalSource, SIGNAL(deleteSelected()), this, SLOT(onDelete()));
        return true;
    }

    return false;
}

bool Nodest::DeleteSelectedConnecitonExtension::checkDependency()
{
    AbstractGraphObject* graphObj = dynamic_cast<AbstractGraphObject*>(parent());
    std::vector<AbstractExtension*> parentExtensions = graphObj->getExtensions();
    for (size_t i = 0; i < parentExtensions.size(); i++){
        if (parentExtensions[i]->getExtensionType() == ExtensionType::GraphConnectionSelection){
            m_graphSelectionExtension = dynamic_cast<GraphConnectionSelectionExtension*>(parentExtensions[i]);
            return true;
        }
    }

    return false;
}

void Nodest::DeleteSelectedConnecitonExtension::onDelete()
{
    //important: there should never be selection of nodes and connections
    //at the same moment, if such functionality is needed, the sequence of deletion
    //must be handled with care

    AbstractGraphObject* graphObject = dynamic_cast<AbstractGraphObject*>(parent());
    std::vector<AbstractConnectionObject*>& selectedConnections = m_graphSelectionExtension->getSelectedConnections();

    for (auto& connectObj : selectedConnections){
        graphObject->removeSingleConnection(connectObj);
    }

    selectedConnections.clear();
}
