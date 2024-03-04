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

    switch(index){

    case 0:
        node = new NF::IntNode();
        break;
    case 1:
        node = new NF::AddIntNode();
        break;
    case 2:
        node = new NF::MultiplyIntNode();
        break;
    case 3:
        node = new NF::MaxIntNode();
        break;
    case 4:
        node = new NF::NegativeIntNode();
        break;
    case 5:
        node = new NF::ClampIntNode();
        break;
    default:
        break;
    }

    if (node == nullptr){
        return;
    }

    NF::AbstractNodeObject* nodeObj = new NF::VerticalNodeObject(node,
                                 NF::uiMap[node->getNameID()], NF::globalGraphObject);
    NF::globalGraphObject->addNodeObject(nodeObj);


}
