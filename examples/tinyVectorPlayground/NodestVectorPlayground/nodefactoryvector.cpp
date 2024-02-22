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
    Nodest::AbstractNode* node = nullptr;

    switch(index){

    case 0:
        node = new Nodest::VectorDisplayNode();
        break;
    case 1:
        node = new Nodest::IntVector4DNode();
        break;
    case 2:
        node = new Nodest::VectorConcatNode();
        break;
    case 3:
        node = new Nodest::VectorSortNode();
        break;
    case 4:
        node = new Nodest::VectorReverseNode();
        break;
    case 5:
        node = new Nodest::VectorSplitNode();
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
