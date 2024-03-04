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

    switch(index){

    case 0:
        node = new NF::VectorDisplayNode();
        break;
    case 1:
        node = new NF::IntVector4DNode();
        break;
    case 2:
        node = new NF::VectorConcatNode();
        break;
    case 3:
        node = new NF::VectorSortNode();
        break;
    case 4:
        node = new NF::VectorReverseNode();
        break;
    case 5:
        node = new NF::VectorSplitNode();
        break;
    case 6:
        node = new NF::VectorPopbackNode();
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
