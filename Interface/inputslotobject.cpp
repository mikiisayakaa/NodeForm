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
    bindWidgets();
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


void Nodest::InputSlotObject::onConnectionDrag(qreal x, qreal y)
{

    if (m_testConnection == nullptr){
        m_testConnection = new TestConnection();
        QQuickItem* line = nullptr;
        QQuickItem* handle = nullptr;

        InputSlot* inSlot = (InputSlot*)m_slot;

        //already have a connection, we'll cut off the existing one
        if (inSlot->getConnection() != nullptr){
            Connection* oldConnection = inSlot->getConnection();
            OutputSlot* outSlot = oldConnection->getFirst();

            m_testConnection->firstNode = outSlot->getParent();
            m_testConnection->firstFlow = 1;
            m_testConnection->firstIndex = outSlot->getIndex();

            //create before removal, or user will see a flash in the ui
            handle = outSlot->getObj()->getItem(0);

            connectionStartHelper(handle);

            line = m_tempConnection->getItem();
            line->setProperty("x2", m_items[0]->property("globalX").toReal() +
                                    m_items[0]->property("width").toReal() / 2);
            line->setProperty("y2", m_items[0]->property("globalY").toReal() +
                                    m_items[0]->property("height").toReal() / 2);

            //remove the original connection
            AbstractGraphObject* graphObj = qobject_cast<AbstractGraphObject*>(NodestGlobal::globalBackground->parent());
            graphObj->removeSingleConnection(oldConnection->getObj());

        }
        else{
            handle = m_items[0];
            m_testConnection->secondNode = m_slot->getParent();
            m_testConnection->secondFlow = 0;
            m_testConnection->secondIndex = m_slot->getIndex();

            connectionStartHelper(handle);
        }
    }
    else{
        QQuickItem* line = m_tempConnection->getItem();

        if (m_testConnection->firstNode == nullptr){
            line->setProperty("x1", x);
            line->setProperty("y1", y);
        }
        else{
            line->setProperty("x2", x);
            line->setProperty("y2", y);
        }

    }

}


