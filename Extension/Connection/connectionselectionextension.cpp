#include "connectionselectionextension.h"

#include "Interface/abstractgraphobject.h"

bool Nodest::ConnectionSelectionExtension::addExtension(QQuickItem *signalSource)
{
    if (checkDependency()){
        connect(signalSource, SIGNAL(select()), this, SLOT(onSelect()));
        return true;
    }
    else{
        return false;
    }
}

bool Nodest::ConnectionSelectionExtension::checkDependency()
{
    ConnectionObject* connectObj = dynamic_cast<ConnectionObject*>(parent());
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

void Nodest::ConnectionSelectionExtension::onSelect()
{
    m_graphSelectionExtension->onDeselect();
    m_graphSelectionExtension->selectOne(dynamic_cast<ConnectionObject*>(parent()));
}
