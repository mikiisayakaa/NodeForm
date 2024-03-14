#include "slotobject.h"
#include "Global/globalitems.h"
#include "Global/globalqmlfiles.h"
#include "Global/globaluiparams.h"
#include "connectionobject.h"
#include "Utils/qmlcreationutils.h"
#include "abstractgraphobject.h"
#include "Extension/extensionfactory.h"
#include "databridgemacro.h"

NF::SlotObject::SlotObject(NF::AbstractSlot *slot, NF::UIParameters* params, QObject *parent)
    :AbstractSlotObject (slot, parent),m_createParams(params)
{
    m_items.resize(3);
    slot->setObj(this);
    createWidgets();
    //do not set widgets layout here, let nodeObject do it
    addExtensions();
}


void NF::SlotObject::createWidgets()
{
    int index = m_slot->getIndex();
    int flow = m_slot->getFlow();
    QString slotName;
    QString handleFile;
    QString nameLabelFile;
    QString dataBridgeFile("");

    if (m_createParams == nullptr){
        slotName = m_slot->getTypeName();
        handleFile = NF::slotHandleDefault;
        nameLabelFile = NF::textLabelDefault;
        NF::getValidDataBridgeFileName(dataBridgeFile, m_slot);
    }
    else{
        slotName = flow == 0 ? m_createParams->inputNames[index] :
                               m_createParams->outputNames[index];

        std::vector<std::vector<QString>>& files = flow == 0 ? m_createParams->inputFiles :
                                                               m_createParams->outputFiles;

        QString handleQuery = files[index][0];
        handleFile = NF::slotHandleMap.contains(handleQuery) ? handleQuery :
                                     NF::slotHandleDefault;
        QString labelQuery = files[index][1];
        nameLabelFile = NF::textLabelMap.contains(labelQuery) ? labelQuery :
                                        NF::textLabelDefault;
        dataBridgeFile = files[index][2];
        //qDebug() << dataBridgeFile;
        getValidDataBridgeFileName(dataBridgeFile, m_slot);
    }

    QQuickItem* parentItem = qobject_cast<AbstractNodeObject*>(parent())->getNodeBase();
    createHandle(handleFile, parentItem, m_items[0], m_slot);
    createTextLabel(nameLabelFile, parentItem, m_items[1], slotName);

    if (dataBridgeFile == NF::dummyFile){
        m_bridge = nullptr;
        createDummy(parentItem, m_items[2]);
        if (m_slot->getFlow() == 0){
            AbstractNodeObject* nodeObj = dynamic_cast<AbstractNodeObject*>(parent());
            nodeObj->getNode()->addDepend(1);
        }
    }
    else{
        if (m_slot->getFlow() == 0){
            m_bridge = NF::GlobalBridgeFactory::createBridge(NF::dataBridgeSetterMap[dataBridgeFile].cppTypeName,
                                                             NF::dataBridgeSetterMap[dataBridgeFile].qmlTypeName);
        }
        else{
            m_bridge = NF::GlobalBridgeFactory::createBridge(NF::dataBridgeGetterMap[dataBridgeFile].cppTypeName,
                                                             NF::dataBridgeGetterMap[dataBridgeFile].qmlTypeName);
        }
        m_bridge->setSlot(m_slot);
        m_bridge->setParent(this);
        QQuickItem* item;
        NF::createDataBridge(dataBridgeFile, parentItem, item, m_bridge, m_slot->getFlow());
        m_items[2] = item;
    }

    m_items[0]->setParent(this);
    m_items[1]->setParent(this);
    m_items[2]->setParent(this);
}


void NF::SlotObject::setWidgetsLayout()
{
    //0-handle, 1-text, 2-setter/getter
    QQuickItem* nodeBase = qobject_cast<AbstractNodeObject*>(parent())->getNodeBase();
    int flow = m_slot->getFlow();

    if (flow == 0){
        setAnchors(m_items[0], nodeBase, "horizontalCenter", "left");
        setAnchors(m_items[1], m_items[0], "left", "right");
        setAnchors(m_items[1], m_items[0], "verticalCenter", "verticalCenter");
        setAnchors(m_items[2], m_items[1], "left", "left");
        setAnchors(m_items[2], m_items[1], "top", "bottom");
    }
    else{
        setAnchors(m_items[0], nodeBase, "horizontalCenter", "right");
        setAnchors(m_items[1], m_items[0], "right", "left");
        setAnchors(m_items[1], m_items[0], "verticalCenter", "verticalCenter");
        setAnchors(m_items[2], m_items[1], "right", "right");
        setAnchors(m_items[2], m_items[1], "top", "bottom");
    }
}


void NF::SlotObject::addExtensions()
{
    int flow = m_slot->getFlow();

    std::vector<ExtensionType> extensionList;

    if (flow == 0){
        extensionList = {
            ExtensionType::InDragAddConnection
        };
    }
    else{
        extensionList = {
            ExtensionType::OutDragAddConnection
        };
    }


    for (auto& type : extensionList){
        AbstractExtension* extension = ExtensionFactory::createExtension(type, this);
        addExtension(extension);
    }
}


