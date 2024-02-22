#include "nodefactoryimage.h"

#include "typedefines.h"
#include "gsdefines.h"
#include "nodedefines.h"
#include "Interface/verticalnodeobject.h"
#include "Global/globalitems.h"
#include "Global/globalqmlfiles.h"

NodeFactoryImage::NodeFactoryImage(QObject *parent) : QObject(parent)
{

}

void NodeFactoryImage::createNode(int index)
{
    Nodest::AbstractNode* node = nullptr;

    switch(index){

    case 0:
        node = new Nodest::DisplayImageNode();
        break;
    case 1:
        node = new Nodest::LoadImageNode();
        break;
    case 2:
        node = new Nodest::InverseImageNode();
        break;
    case 3:
        node = new Nodest::BrightnessNode();
        break;
    case 4:
        node = new Nodest::GrayScaleNode();
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
