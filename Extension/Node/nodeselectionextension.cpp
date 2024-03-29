#include "nodeselectionextension.h"
#include "Interface/abstractnodeobject.h"
#include "Interface/abstractgraphobject.h"
#include "Extension/Graph/graphnodeselectionextension.h"

bool NF::NodeSelectionExtension::addExtension(QQuickItem *signalSource)
{
    if (checkDependency()){
        connect(signalSource, SIGNAL(select()), this, SLOT(onSelect()));
        return true;
    }
    else{
        return false;
    }
}

bool NF::NodeSelectionExtension::checkDependency()
{
    AbstractNodeObject* nodeObj = dynamic_cast<AbstractNodeObject*>(parent());
    AbstractGraphObject* graphObj = dynamic_cast<AbstractGraphObject*>(nodeObj->parent());
    std::vector<AbstractExtension*> parentExtensions = graphObj->getExtensions();
    for (size_t i = 0; i < parentExtensions.size(); i++){
        if (parentExtensions[i]->getExtensionType() == ExtensionType::GraphNodeSelection){
            m_graphSelectionExtension = dynamic_cast<GraphNodeSelectionExtension*>(parentExtensions[i]);
            return true;
        }
    }

    return false;
}

void NF::NodeSelectionExtension::onSelect()
{
    m_graphSelectionExtension->onDeselect();
    m_graphSelectionExtension->selectOne(dynamic_cast<AbstractNodeObject*>(parent()));
}
