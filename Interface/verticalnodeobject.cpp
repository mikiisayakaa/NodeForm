#include "verticalnodeobject.h"
#include "Global/globalqmlfiles.h"
#include "abstractgraphobject.h"
#include "basicgraphobject.h"
#include "Utils/qmlcreationutils.h"
#include "slotobject.h"
#include "Extension/extensionfactory.h"



Nodest::VerticalNodeObject::VerticalNodeObject(Nodest::AbstractNode *node, NodestGlobal::UIParameters *params, QObject *parent)
    : AbstractNodeObject (node, parent), m_createParams(params)
{
    m_items.resize(1);
    m_inputObjects.resize(m_node->getNInput());
    m_outputObjects.resize(m_node->getNOutput());

    createWidgets();
    setWidgetsLayout();
    addExtensions();
}

void Nodest::VerticalNodeObject::createWidgets()
{
    QString nodeName;
    QString nodeBaseFile;
    QString nameLabelFile;

    if (m_createParams == nullptr){
        nodeName = m_node->getNameID();
        nodeBaseFile = NodestGlobal::nodeBaseDefault;
        nameLabelFile = NodestGlobal::textLabelDefault;
    }
    else{
        nodeName = m_createParams->nodeName;

        QString baseQuery = m_createParams->baseFiles[0];
        nodeBaseFile = NodestGlobal::nodeBaseMap.contains(baseQuery) ? baseQuery :
                                     NodestGlobal::nodeBaseDefault;
        QString labelQuery = m_createParams->baseFiles[1];
        nameLabelFile = NodestGlobal::textLabelMap.contains(labelQuery) ? labelQuery :
                                        NodestGlobal::textLabelDefault;
    }

    QQuickItem* parentItem = qobject_cast<AbstractGraphObject*>(parent())->getBackground();
    createBase(nodeBaseFile, parentItem, m_nodeBase);

    createTextLabel(nameLabelFile, m_nodeBase, m_items[0], nodeName);

    m_nodeBase->setParent(this);
    m_items[0]->setParent(this);

    //create InputSlotObjects
    for (size_t i = 0; i < m_node->getNInput(); i++){
        InputSlot* inSlot = m_node->getInput(i);
        AbstractSlotObject* slotObj = new SlotObject(inSlot, m_createParams, this);
        m_inputObjects[i] = slotObj;
    }

    //create OutputSlotObjects
    for (size_t i = 0; i < m_node->getNOutput(); i++){
        OutputSlot* outSlot = m_node->getOutput(i);
        AbstractSlotObject* slotObj = new SlotObject(outSlot, m_createParams, this);
        m_outputObjects[i] = slotObj;
    }

    //bind setters to update function
    for (size_t i = 0; i < m_node->getNInput(); i++){
        InputSlot* inSlot = m_node->getInput(i);
        if (inSlot->getSetter() != nullptr){
            connect(inSlot->getSetter(), SIGNAL(updated()), this, SLOT(onInputChanged()));
        }
    }
}


void Nodest::VerticalNodeObject::addExtensions()
{
    std::vector<ExtensionType> extensionList{
        ExtensionType::NodeSelection,
        ExtensionType::MoveNode
    };

    for (auto& type : extensionList){
        AbstractExtension* ext = ExtensionFactory::createExtension(type, this);
        addExtension(ext);
    }
}

void Nodest::VerticalNodeObject::setWidgetsLayout()
{
    QQuickItem* lastItem;
    lastItem = m_nodeBase;

    //trick here: we set width twice, if we let width be 0 and
    //do setWidgetsLayout for each slot, childrenRect's width will be larger than expected
    m_nodeBase->setProperty("width", m_nodeBase->childrenRect().width());

    //put the node name label at center top
    setAnchors(m_items[0], lastItem, "top", "top");
    setAnchors(m_items[0], lastItem, "horizontalCenter", "horizontalCenter");
    lastItem = m_items[0];

    //put the output handles and textlabels
    for (size_t i = 0; i < m_node->getNOutput(); i++){
        setAnchors(m_outputObjects[i]->getItem(0), lastItem, "top", "bottom");
        m_outputObjects[i]->setWidgetsLayout();
        lastItem = m_outputObjects[i]->getItem(2);
    }

    //put the input handles, textlabels and setters
    for (size_t i = 0; i < m_node->getNInput(); i++){
        setAnchors(m_inputObjects[i]->getItem(0), lastItem, "top", "bottom");
        m_inputObjects[i]->setWidgetsLayout();
        lastItem = m_inputObjects[i]->getItem(2);
    }

    m_nodeBase->setProperty("width", m_nodeBase->childrenRect().width() + 10);
    m_nodeBase->setProperty("minWidth", m_nodeBase->width());
    m_nodeBase->setProperty("height", m_nodeBase->childrenRect().height() + 10);
}

Nodest::VerticalNodeObject *Nodest::VerticalNodeObject::clone()
{
    AbstractNode* nodeCopy = m_node->clone();
    VerticalNodeObject* nodeObj = new VerticalNodeObject(nodeCopy, m_createParams, parent());

    nodeObj->getNodeBase()->setProperty("x", m_nodeBase->property("x").toReal() + 50);
    nodeObj->getNodeBase()->setProperty("y", m_nodeBase->property("y").toReal() + 50);

    return nodeObj;
}

void Nodest::VerticalNodeObject::onInputChanged()
{
    if (parent()){
        qobject_cast<AbstractGraphObject*>(parent())->reEvalSingle(this);
    }
}


