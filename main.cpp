#include <QApplication>
#include <QDebug>
#include <QHash>

#include "Global/globalinit.h"

#include "Global/typenamemacro.h"
#include "Global/typenameregistry.h"
#include "Global/globalitems.h"
#include "Wrapper/slotgettersetter.h"

#include "NodeTypes/Numeric/numericnodes.h"
#include "Interface/verticalnodeobject.h"
#include "Interface/basicgraphobject.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    NodestGlobal::globalInit(&app);

    qDebug() << Nodest::TYPENAME<int>::getID();
    qDebug() << Nodest::TYPENAME<float>::getID();
    qDebug() << Nodest::TYPENAME<QString>::getID();
    qDebug() << Nodest::TYPENAME<QHash<int,int>>::getName();

//    Nodest::AbstractSlotGetter* setter = new Nodest::IntSlotGetter(nullptr);

//    Nodest::AbstractNode* node1 = new NodestNumeric::AddIntNode();
//    Nodest::AbstractNodeObject* nodeObj1 = new Nodest::VerticalNodeObject(node1,
//                                            NodestGlobal::uiMap[node1->getNameID()], NodestGlobal::globalGraphObject);

//    Nodest::AbstractNode* node2 = new NodestNumeric::AddIntNode();
//    Nodest::AbstractNodeObject* nodeObj2 = new Nodest::VerticalNodeObject(node2,
//                                            NodestGlobal::uiMap[node2->getNameID()], NodestGlobal::globalGraphObject);

//    Nodest::AbstractNode* node3 = new NodestNumeric::RandomIntNode();
//    Nodest::AbstractNodeObject* nodeObj3 = new Nodest::VerticalNodeObject(node3,
//                                            NodestGlobal::uiMap[node3->getNameID()], NodestGlobal::globalGraphObject);


//    Nodest::AbstractNode* node4 = new NodestNumeric::IntNode();
//    Nodest::AbstractNodeObject* nodeObj4 = new Nodest::VerticalNodeObject(node4,
//                                            NodestGlobal::uiMap[node4->getNameID()], NodestGlobal::globalGraphObject);
//    NodestGlobal::globalGraphObject->addNodeObject(nodeObj1);
//    NodestGlobal::globalGraphObject->addNodeObject(nodeObj2);
//    NodestGlobal::globalGraphObject->addNodeObject(nodeObj3);
//    NodestGlobal::globalGraphObject->addNodeObject(nodeObj4);

    return app.exec();
}
