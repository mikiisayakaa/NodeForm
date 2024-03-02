#include "indragaddconnectionextension.h"

#include "Interface/abstractgraphobject.h"
#include "Global/globalqmlfiles.h"
#include "Global/globaluiparams.h"
#include "Global/globalitems.h"
#include "Interface/tempconnectionobject.h"
#include "Interface/connectionobject.h"
#include "Utils/qmlcreationutils.h"

Nodest::InDragAddConnectionExtension::InDragAddConnectionExtension(QObject *parent) :
    DragAddConnectionExtension(parent)
{
    m_extensionName = "InDragAddConnection";
    m_type = ExtensionType::InDragAddConnection;
}

bool Nodest::InDragAddConnectionExtension::addExtension(QQuickItem *signalSource)
{
    if (signalSource->property("dummy").isValid()){
        return false;
    }

    if (signalSource->property("flow").toInt() == 1){
        return false;
    }
    connect(signalSource, SIGNAL(connectionEnd(qreal, qreal)), this, SLOT(onConnectionEnd(qreal, qreal)));
    connect(signalSource, SIGNAL(position(qreal, qreal)), this, SLOT(onConnectionDrag(qreal, qreal)));
    m_handle = signalSource;
    return true;
}

void Nodest::InDragAddConnectionExtension::onConnectionDrag(qreal x, qreal y)
{
    AbstractSlot* slot = dynamic_cast<AbstractSlotObject*>(parent())->getSlot();

    if (m_testConnection == nullptr){
        m_testConnection = new TestConnection();
        QQuickItem* line = nullptr;
        QQuickItem* handle = nullptr;

        InputSlot* inSlot = (InputSlot*)slot;

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

            m_line->setProperty("x2", m_handle->property("globalX").toReal() +
                                    m_handle->property("width").toReal() / 2);
            m_line->setProperty("y2", m_handle->property("globalY").toReal() +
                                    m_handle->property("height").toReal() / 2);

            //remove the original connection
            AbstractGraphObject* graphObj = qobject_cast<AbstractGraphObject*>(parent()->parent()->parent());
            graphObj->removeSingleConnection(oldConnection->getObj());

        }
        else{
            handle = m_handle;
            m_testConnection->secondNode = slot->getParent();
            m_testConnection->secondFlow = 0;
            m_testConnection->secondIndex = slot->getIndex();

            connectionStartHelper(m_handle);
        }
    }
    else{
        if (m_testConnection->firstNode == nullptr){
            m_line->setProperty("x1", x);
            m_line->setProperty("y1", y);
        }
        else{
            m_line->setProperty("x2", x);
            m_line->setProperty("y2", y);
        }

    }
}
