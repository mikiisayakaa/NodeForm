#include "slotobject.h"
#include "Global/globalitems.h"
#include "Global/globalqmlfiles.h"
#include "Global/globaluiparams.h"
#include "connectionobject.h"
#include "tempconnectionobject.h"
#include "Utils/qmlcreationutils.h"
#include "abstractgraphobject.h"
#include "Extension/extensionfactory.h"

Nodest::SlotObject::SlotObject(Nodest::AbstractSlot *slot, NodestGlobal::UIParameters* params, QObject *parent)
    :AbstractSlotObject (slot, parent),m_createParams(params)
{
    m_items.resize(3);
    slot->setObj(this);
    createWidgets();
    //do not set widgets layout here, let nodeObject do it
    addExtensions();
}

void Nodest::SlotObject::createWidgets()
{
    int index = m_slot->getIndex();
    int flow = m_slot->getFlow();
    QString slotName;
    QString handleFile;
    QString nameLabelFile;
    QString gsFile;

    if (m_createParams == nullptr){
        slotName = m_slot->getTypeName();
        handleFile = NodestGlobal::slotHandleDefault;
        nameLabelFile = NodestGlobal::textLabelDefault;

        if (flow == 0){
            getValidSetterFileName(gsFile, (InputSlot*)m_slot);
        }
        else{
            getValidGetterFileName(gsFile, (OutputSlot*)m_slot);
        }
    }
    else{
        slotName = m_createParams->inputNames[index];

        std::vector<std::vector<QString>>& files = flow == 0 ? m_createParams->inputFiles : m_createParams->outputFiles;

        QString handleQuery = files[index][0];
        handleFile = NodestGlobal::slotHandleMap.contains(handleQuery) ? handleQuery :
                                     NodestGlobal::slotHandleDefault;
        QString labelQuery = files[index][1];
        nameLabelFile = NodestGlobal::textLabelMap.contains(labelQuery) ? labelQuery :
                                        NodestGlobal::textLabelDefault;
        QString gsQuery = files[index][2];

        if (flow == 0){
            getValidSetterFileName(gsQuery, (InputSlot*)m_slot);
        }
        else{
            getValidGetterFileName(gsQuery, (OutputSlot*)m_slot);
        }

        gsFile = gsQuery;
    }

    QQuickItem* parentItem = qobject_cast<AbstractNodeObject*>(parent())->getNodeBase();
    createHandle(handleFile, parentItem, m_items[0], m_slot);
    createTextLabel(nameLabelFile, parentItem, m_items[1], slotName);

    if (flow == 0){
        createSetter(gsFile, parentItem, m_items[2], m_slot);
    }
    else{
        createGetter(gsFile, parentItem, m_items[2], m_slot);
    }

    m_items[0]->setParent(this);
    m_items[1]->setParent(this);
    m_items[2]->setParent(this);
}

void Nodest::SlotObject::setWidgetsLayout()
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


void Nodest::SlotObject::addExtensions()
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


