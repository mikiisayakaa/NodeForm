#include "nodefactory.h"

#include "typedefines.h"
#include "gsdefines.h"
#include "nodedefines.h"
#include "Interface/verticalnodeobject.h"
#include "Global/globalitems.h"
#include "Global/globalqmlfiles.h"

NodeFactory::NodeFactory(QObject *parent) : QObject(parent)
{

}

void NodeFactory::createNode(int index)
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

QString NodeFactory::getNodeName(int index)
{
    return NF::GlobalNodeFactory::getNodeNameFromID(index);
}

int NodeFactory::getNodeNum()
{
    return NF::GlobalNodeFactory::getNodeNum();
}
