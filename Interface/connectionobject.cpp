#include "connectionobject.h"
#include "abstractgraphobject.h"
#include "basicgraphobject.h"


void Nodest::ConnectionObject::onSelected()
{
    m_connectionItem->setProperty("colorValue", "yellow");
    m_connectionItem->setProperty("select", true);
    BasicGraphObject* graphObj = qobject_cast<BasicGraphObject*>(parent());
    graphObj->clearNodeSelection();
    graphObj->clearConnectionSelection();
    graphObj->getSelectedConnects().push_back(this);
}
