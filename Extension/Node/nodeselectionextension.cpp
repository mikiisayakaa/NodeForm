#include "nodeselectionextension.h"
#include "Interface/abstractnodeobject.h"
#include "Interface/abstractgraphobject.h"

bool Nodest::NodeSelectionExtension::addExtension(QQuickItem *signalSource)
{
    if (checkDependency()){
        connect(signalSource, SIGNAL(select()), this, SLOT(onSelect()));
        return true;
    }
    else{
        return false;
    }
}

bool Nodest::NodeSelectionExtension::checkDependency()
{
    std::vector<AbstractExtension*> parentExtensions = ((AbstractGraphObject*)parent())->getExtensions();
    for (size_t i = 0; i < parentExtensions.size(); i++){
        if (parentExtensions[i]->getExtensionName() == "GraphNodeSelection"){
            return true;
        }
    }

    return false;
}

void Nodest::NodeSelectionExtension::onSelect()
{
    m_graphSelectionExtension->selectOne((AbstractNodeObject*)(parent()));
}
