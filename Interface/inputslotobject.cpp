#include "inputslotobject.h"
#include "Utils/qmlcreationutils.h"
#include "Global/globalqmlfiles.h"
#include "Global/globalitems.h"
#include "abstractnodeobject.h"
#include "abstractgraphobject.h"


Nodest::InputSlotObject::InputSlotObject(Nodest::InputSlot *slot, NodestGlobal::UIParameters* params, QObject *parent)
    : SlotObject(slot, parent), m_createParams(params)
{
    m_items.resize(3);
    slot->setObj(this);
    createWidgets();
    addExtensions();
}

void Nodest::InputSlotObject::createWidgets()
{
    int index = m_slot->getIndex();
    QString slotName;
    QString handleFile;
    QString nameLabelFile;
    QString setterFile;

    if (m_createParams == nullptr){
        slotName = m_slot->getTypeName();
        handleFile = NodestGlobal::slotHandleDefault;
        nameLabelFile = NodestGlobal::textLabelDefault;

        getValidSetterFileName(setterFile, (InputSlot*)m_slot);
    }
    else{
        slotName = m_createParams->inputNames[index];

        QString handleQuery = m_createParams->inputFiles[index][0];
        handleFile = NodestGlobal::slotHandleMap.contains(handleQuery) ? handleQuery :
                                     NodestGlobal::slotHandleDefault;
        QString labelQuery = m_createParams->inputFiles[index][1];
        nameLabelFile = NodestGlobal::textLabelMap.contains(labelQuery) ? labelQuery :
                                        NodestGlobal::textLabelDefault;
        QString setterQuery = m_createParams->inputFiles[index][2];
        getValidSetterFileName(setterQuery, (InputSlot*)m_slot);
        setterFile = setterQuery;
    }

    QQuickItem* parentItem = qobject_cast<AbstractNodeObject*>(parent())->getNodeBase();
    createHandle(handleFile, parentItem, m_items[0], m_slot);
    createTextLabel(nameLabelFile, parentItem, m_items[1], slotName);
    createSetter(setterFile, parentItem, m_items[2], m_slot);

    m_items[0]->setParent(this);
    m_items[1]->setParent(this);
    m_items[2]->setParent(this);
}

void Nodest::InputSlotObject::setWidgetsLayout()
{
    //0-handle, 1-text, 2-setter/getter
    QQuickItem* nodeBase = qobject_cast<AbstractNodeObject*>(parent())->getNodeBase();
    setAnchors(m_items[0], nodeBase, "horizontalCenter", "left");
    setAnchors(m_items[1], m_items[0], "left", "right");
    setAnchors(m_items[1], m_items[0], "verticalCenter", "verticalCenter");
    setAnchors(m_items[2], m_items[1], "left", "left");
    setAnchors(m_items[2], m_items[1], "top", "bottom");
}


