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
    NF::AbstractNode* node = nullptr;

    switch(index){

    case 0:
        node = new NF::DisplayImageNode();
        break;
    case 1:
        node = new NF::LoadImageNode();
        break;
    case 2:
        node = new NF::InverseImageNode();
        break;
    case 3:
        node = new NF::BrightnessNode();
        break;
    case 4:
        node = new NF::GrayScaleNode();
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
