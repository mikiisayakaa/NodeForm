#include "basicgraphobject.h"
#include "Global/globalitems.h"
#include "Global/globalqmlfiles.h"

#include "Extension/extensionfactory.h"

Nodest::BasicGraphObject::BasicGraphObject(AbstractNodeGraph *graph, QObject *parent)
    : AbstractGraphObject (graph, parent)
{
    createWidgets();
    addExtensions();
}

void Nodest::BasicGraphObject::createWidgets()
{
    QQuickItem* parentItem = NodestGlobal::globalRootObject;

    QQmlComponent* component = NodestGlobal::backgroundMap[NodestGlobal::backgroundDefault];

    QObject* bgdObject = component->beginCreate(NodestGlobal::engine->rootContext());
    m_background = qobject_cast<QQuickItem*>(bgdObject);
    m_background->setParentItem(parentItem);
    m_background->setParent(this);

    NodestGlobal::globalBackground = m_background;

    component->completeCreate();
}


void Nodest::BasicGraphObject::addExtensions()
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



//void Nodest::BasicGraphObject::onPreCopy()
//{
//    m_nodeObjectsToCopy = m_selectedNodeObjects;
//}

//void Nodest::BasicGraphObject::onCopy()
//{
//    for (size_t i = 0; i < m_selectedNodeObjects.size(); i++){
//        copyNodeObj(m_selectedNodeObjects[i]);
//    }
//}

