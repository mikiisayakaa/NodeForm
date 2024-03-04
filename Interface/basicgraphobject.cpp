#include "basicgraphobject.h"
#include "Global/globalitems.h"
#include "Global/globalqmlfiles.h"

#include "Extension/extensionfactory.h"

NF::BasicGraphObject::BasicGraphObject(AbstractNodeGraph *graph, QObject *parent)
    : AbstractGraphObject (graph, parent)
{
    createWidgets();
    addExtensions();
}

void NF::BasicGraphObject::createWidgets()
{
    QQuickItem* parentItem = NF::globalRootObject;

    QQmlComponent* component = NF::backgroundMap[NF::backgroundDefault];

    QObject* bgdObject = component->beginCreate(NF::engine->rootContext());
    m_background = qobject_cast<QQuickItem*>(bgdObject);
    m_background->setParentItem(parentItem);
    m_background->setParent(this);

    NF::globalBackground = m_background;

    component->completeCreate();
}


void NF::BasicGraphObject::addExtensions()
{
    std::vector<ExtensionType> extensionList{
        ExtensionType::GraphNodeSelection,
        ExtensionType::GraphConnectionSelection,
        ExtensionType::MoveBackground,
        ExtensionType::ScaleBackground,
        ExtensionType::DeleteSelectedNode,
        ExtensionType::DeleteSelectedConnection
    };

    for (auto& type : extensionList){
        AbstractExtension* ext = ExtensionFactory::createExtension(type, this);
        addExtension(ext);
    }
}



//void NF::BasicGraphObject::onPreCopy()
//{
//    m_nodeObjectsToCopy = m_selectedNodeObjects;
//}

//void NF::BasicGraphObject::onCopy()
//{
//    for (size_t i = 0; i < m_selectedNodeObjects.size(); i++){
//        copyNodeObj(m_selectedNodeObjects[i]);
//    }
//}

