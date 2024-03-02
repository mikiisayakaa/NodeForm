#include "outputslotobject.h"
#include "Global/globalqmlfiles.h"
#include "Utils/qmlcreationutils.h"
#include "abstractnodeobject.h"
#include "Global/globalitems.h"
#include "Global/globalqmlfiles.h"
#include "abstractgraphobject.h"
#include "abstractnodeobject.h"


Nodest::OutputSlotObject::OutputSlotObject(Nodest::OutputSlot *slot, NodestGlobal::UIParameters* params, QObject *parent)
    : SlotObject (slot, parent), m_createParams(params)
{
    m_items.resize(3);
    slot->setObj(this);
    createWidgets();
    bindWidgets();
    addExtensions();
}

Nodest::OutputSlotObject::~OutputSlotObject()
{

}

void Nodest::OutputSlotObject::createWidgets()
{
    int index = m_slot->getIndex();
    QString slotName;
    QString handleFile;
    QString nameLabelFile;
    QString getterFile;

    if (m_createParams == nullptr){
        slotName = m_slot->getTypeName();
        handleFile = NodestGlobal::slotHandleDefault;
        nameLabelFile = NodestGlobal::textLabelDefault;

        getValidGetterFileName(getterFile, (OutputSlot*)m_slot);
    }
    else{
        slotName = m_createParams->outputNames[index];

        QString handleQuery = m_createParams->outputFiles[index][0];
        handleFile = NodestGlobal::slotHandleMap.contains(handleQuery) ? handleQuery :
                                     NodestGlobal::slotHandleDefault;
        QString labelQuery = m_createParams->outputFiles[index][1];
        nameLabelFile = NodestGlobal::textLabelMap.contains(labelQuery) ? labelQuery :
                                        NodestGlobal::textLabelDefault;
        QString getterQuery = m_createParams->outputFiles[index][2];
        getValidGetterFileName(getterQuery, (OutputSlot*)m_slot);
        getterFile = getterQuery;
    }


    QQuickItem* parentItem = qobject_cast<AbstractNodeObject*>(parent())->getNodeBase();
    createHandle(handleFile, parentItem, m_items[0], m_slot);
    createTextLabel(nameLabelFile, parentItem, m_items[1], slotName);
    createGetter(getterFile, parentItem, m_items[2], (OutputSlot*)m_slot);

    m_items[0]->setParent(this);
    m_items[1]->setParent(this);
    m_items[2]->setParent(this);
}

void Nodest::OutputSlotObject::setWidgetsLayout()
{
    QQuickItem* nodeBase = qobject_cast<AbstractNodeObject*>(parent())->getNodeBase();
    setAnchors(m_items[0], nodeBase, "horizontalCenter", "right");
    setAnchors(m_items[1], m_items[0], "right", "left");
    setAnchors(m_items[1], m_items[0], "verticalCenter", "verticalCenter");
    setAnchors(m_items[2], m_items[1], "right", "right");
    setAnchors(m_items[2], m_items[1], "top", "bottom");
}



void Nodest::OutputSlotObject::onConnectionDrag(qreal x, qreal y)
{
    if (m_testConnection == nullptr){
        m_testConnection = new TestConnection();
        m_testConnection->firstNode = m_slot->getParent();
        m_testConnection->firstFlow = 1;
        m_testConnection->firstIndex = m_slot->getIndex();

        connectionStartHelper(m_items[0]);
    }
    else{
        QQuickItem* line = m_tempConnection->getItem();

        line->setProperty("x2", x);
        line->setProperty("y2", y);
    }
}

