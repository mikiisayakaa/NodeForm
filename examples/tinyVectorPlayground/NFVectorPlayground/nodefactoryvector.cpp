#include "nodefactoryvector.h"

#include "typedefines.h"
#include "gsdefines.h"
#include "nodedefines.h"
#include "Interface/verticalnodeobject.h"
#include "Global/globalitems.h"
#include "Global/globalqmlfiles.h"

NodeFactoryVector::NodeFactoryVector(QObject *parent) : QObject(parent)
{

}

void NodeFactoryVector::createNode(int index)
{
    NF::AbstractNode* node = nullptr;

    node = NF::GlobalNodeFactory::createNode(index);

    if (node == nullptr){
        return;
    }

    NF::AbstractNodeObject* nodeObj = new NF::VerticalNodeObject(node,
                                 NF::uiMap[node->getNameID()], NF::globalGraphObject);
    NF::globalGraphObject->addNodeObject(nodeObj);
}
