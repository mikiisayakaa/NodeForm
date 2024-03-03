
#include <QApplication>
#include <QDebug>
#include <QDir>

#include "Global/globalinit.h"
#include "Global/globalpaths.h"

#include "Global/globalitems.h"

#include "Extension/abstractextension.h"
#include "Extension/Graph/deleteselectednodeextension.h"
#include "Extension/Node/nodeselectionextension.h"

#include "nodefactory.h"
#include "typedefines.h"

#include "Utils/variant.h"
#include <iostream>
#include <QRandomGenerator>

using namespace Nodest;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NodestGlobal::setPath(NodestGlobal::nodeJsonPaths, QDir::currentPath() + "/../LargeScaleTest/UI/");
    NodestGlobal::setQmlMain(QDir::currentPath() + "/../LargeScaleTest/Controls/main.qml");
    qmlRegisterType<NodeFactory>("CppObjects", 1, 0, "NodeFactory");
    NodestGlobal::globalInit(&a);

    NodeFactory fac;
    int num = 20;

    std::vector<AbstractNodeObject*> nodes;

    for (int i = 0; i < num; i++){
        fac.createNode(QRandomGenerator::global()->bounded(6));
    }

    for (int i = 0; i < num; i++){
        nodes.push_back(NodestGlobal::globalGraphObject->getNodeObject(i));
    }

    std::vector<AbstractExtension*> exts = NodestGlobal::globalGraphObject->getExtensions();
    DeleteSelectedNodeExtension* deleteNodeExt;
    NodeSelectionExtension* selectExt;
    for (int i = 0; i < exts.size(); i++){
        if (exts[i]->getExtensionType() == ExtensionType::DeleteSelectedNode){
            deleteNodeExt = (DeleteSelectedNodeExtension*)exts[i];
            break;
        }
    }

    for (int i = 0; i < num; i++){
        int n1 = QRandomGenerator::global()->bounded(num);
        int n2 = QRandomGenerator::global()->bounded(num);

        AbstractNode* node1 = nodes[n1]->getNode();
        AbstractNode* node2 = nodes[n2]->getNode();
        int ind1 = 0;
        int ind2 = QRandomGenerator::global()->bounded(node2->getNInput());

        TestConnection* test = new TestConnection(node1, ind1, 1, node2, ind2, 0);
        NodestGlobal::globalGraphObject->addSingleConnection(test);
    }



//    for (int i = 0; i < 1000; i++){
//        std::vector<AbstractExtension*> exts1 = nodes[i]->getExtensions();
//        for (int j = 0; j < exts.size(); j++){
//            if (exts1[j]->getExtensionType() == ExtensionType::NodeSelection){
//                selectExt = (NodeSelectionExtension*)exts1[j];
//                break;
//            }

//        }
//        selectExt->onSelect();
//        deleteNodeExt->onDelete();
//    }




    return a.exec();
}
