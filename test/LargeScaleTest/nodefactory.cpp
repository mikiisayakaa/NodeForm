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
    Nodest::AbstractNode* node = nullptr;

    switch(index){

    case 0:
        node = new Nodest::IntNode();
        break;
    case 1:
        node = new Nodest::AddIntNode();
        break;
    case 2:
        node = new Nodest::MultiplyIntNode();
        break;
    case 3:
        node = new Nodest::MaxIntNode();
        break;
    case 4:
        node = new Nodest::NegativeIntNode();
        break;
    case 5:
        node = new Nodest::ClampIntNode();
        break;
    default:
        break;
    }

    if (node == nullptr){
        return;
    }

    Nodest::AbstractNodeObject* nodeObj = new Nodest::VerticalNodeObject(node,
                                 NodestGlobal::uiMap[node->getNameID()], NodestGlobal::globalGraphObject);
    NodestGlobal::globalGraphObject->addNodeObject(nodeObj);


}
