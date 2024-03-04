#include "connectionselectionextension.h"

#include "Interface/abstractgraphobject.h"
#include "Interface/abstractconnectionobject.h"

bool NF::ConnectionSelectionExtension::addExtension(QQuickItem *signalSource)
{
    if (checkDependency()){
        connect(signalSource, SIGNAL(select()), this, SLOT(onSelect()));
        return true;
    }
    else{
        return false;
    }
}

bool NF::ConnectionSelectionExtension::checkDependency()
{
    AbstractConnectionObject* connectObj = dynamic_cast<AbstractConnectionObject*>(parent());
    AbstractGraphObject* graphObj = dynamic_cast<AbstractGraphObject*>(connectObj->parent());
    std::vector<AbstractExtension*> parentExtensions = graphObj->getExtensions();
    for (size_t i = 0; i < parentExtensions.size(); i++){
        if (parentExtensions[i]->getExtensionType() == ExtensionType::GraphConnectionSelection){
            m_graphSelectionExtension = dynamic_cast<GraphConnectionSelectionExtension*>(parentExtensions[i]);
            return true;
        }
    }

    return false;
}

void NF::ConnectionSelectionExtension::onSelect()
{
    m_graphSelectionExtension->onDeselect();
    m_graphSelectionExtension->selectOne(dynamic_cast<AbstractConnectionObject*>(parent()));
}
