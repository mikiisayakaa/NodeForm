#include "basicgraphobject.h"
#include "Global/globalitems.h"
#include "Global/globalqmlfiles.h"

#include "Extension/extensionfactory.h"

Nodest::BasicGraphObject::BasicGraphObject(AbstractNodeGraph *graph, QObject *parent)
    : AbstractGraphObject (graph, parent)
{
    createWidgets();
    bindWidgets();
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

void Nodest::BasicGraphObject::bindWidgets()
{
//    connect(m_background, SIGNAL(deletePressed()), this, SLOT(onDeletePressed()));

//    connect(m_background, SIGNAL(preCopy()), this, SLOT(onPreCopy()));
//    connect(m_background, SIGNAL(copy()), this, SLOT(onCopy()));
}

void Nodest::BasicGraphObject::addExtensions()
{
    std::vector<ExtensionType> extensionList{
        ExtensionType::GraphNodeSelection,
        ExtensionType::GraphConnectionSelection,
        ExtensionType::MoveBackground
    };

    for (auto& type : extensionList){
        AbstractExtension* ext = ExtensionFactory::createExtension(type, this);
        addExtension(ext);
    }
}




//void Nodest::BasicGraphObject::onDeletePressed()
//{
//    Q_ASSERT_X(m_selectedNodeObjects.empty() || m_selectedConnectObjects.empty(),
//               "abstractgraphobject.cpp", "Error: cannot select both nodes and connections!");

//    if (!m_selectedNodeObjects.empty()){
//        for (size_t i = 0; i < m_selectedNodeObjects.size(); i++){
//            removeNodeObject(m_selectedNodeObjects[i]);
//        }
//        m_selectedNodeObjects.clear();
//        return;
//    }

//    if (!m_selectedConnectObjects.empty()){
//        for (size_t i = 0; i < m_selectedConnectObjects.size(); i++){
//            m_graph->removeSingleConnection(m_selectedConnectObjects[i]->getConnection());
//        }
//        m_selectedConnectObjects.clear();
//        return;
//    }
//}

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

