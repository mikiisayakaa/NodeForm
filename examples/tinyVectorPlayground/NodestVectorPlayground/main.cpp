#include <QApplication>

#include "Global/globalinit.h"
#include "Global/globalpaths.h"

#include "Global/globalitems.h"

#include "nodefactoryvector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NodestGlobal::setPath(NodestGlobal::nodeJsonPath,
                          "D:/C++/Nodest/Nodest/examples/tinyVectorPlayground/NodestVectorPlayground/UI/");
    NodestGlobal::setPath(NodestGlobal::qmlMainPath,
                          "D:/C++/Nodest/Nodest/examples/tinyVectorPlayground/NodestVectorPlayground/Controls/");
    NodestGlobal::setPath(NodestGlobal::qmlGettersPath,
                          "D:/C++/Nodest/Nodest/examples/tinyVectorPlayground/NodestVectorPlayground/Controls/Getters/");
    qmlRegisterType<NodeFactoryVector>("CppObjects", 1, 0, "NodeFactory");
    NodestGlobal::globalInit(&a);



    return a.exec();
}
