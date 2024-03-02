#include "outdragaddconnectionextension.h"
#include "Interface/abstractgraphobject.h"
#include "Global/globalqmlfiles.h"
#include "Global/globaluiparams.h"
#include "Global/globalitems.h"
#include "Interface/connectionobject.h"
#include "Utils/qmlcreationutils.h"


Nodest::OutDragAddConnectionExtension::OutDragAddConnectionExtension(QObject *parent) :
    DragAddConnectionExtension(parent)
{
    m_extensionName = "OutDragAddConnection";
    m_type = ExtensionType::OutDragAddConnection;
}

bool Nodest::OutDragAddConnectionExtension::addExtension(QQuickItem *signalSource)
{
    if (signalSource->property("dummy").isValid()){
        return false;
    }

    if (signalSource->property("flow").toInt() == 0){
        return false;
    }

    connect(signalSource, SIGNAL(connectionEnd(qreal, qreal)), this, SLOT(onConnectionEnd(qreal, qreal)));
    connect(signalSource, SIGNAL(position(qreal, qreal)), this, SLOT(onConnectionDrag(qreal, qreal)));
    m_handle = signalSource;
    return true;
}

void Nodest::OutDragAddConnectionExtension::onConnectionDrag(qreal x, qreal y)
{
    AbstractSlot* slot = dynamic_cast<AbstractSlotObject*>(parent())->getSlot();

    if (m_testConnection == nullptr){
        m_testConnection = new TestConnection();
        m_testConnection->firstNode = slot->getParent();
        m_testConnection->firstFlow = 1;
        m_testConnection->firstIndex = slot->getIndex();

        connectionStartHelper(m_handle);
    }
    else{
        //QQuickItem* line = m_tempConnection->getItem();

        m_line->setProperty("x2", x);
        m_line->setProperty("y2", y);
    }
}
