#include <QApplication>

#include "Global/globalinit.h"
#include "Global/globalpaths.h"

#include "Global/globalitems.h"

#include "nodefactoryvector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NodestGlobal::setPath(NodestGlobal::nodeJsonPaths,
                          "D:/C++/Nodest/Nodest/examples/tinyVectorPlayground/NodestVectorPlayground/UI/");
    NodestGlobal::setQmlMain("D:/C++/Nodest/Nodest/examples/tinyVectorPlayground/NodestVectorPlayground/Controls/main.qml");
    NodestGlobal::setPath(NodestGlobal::qmlGettersPaths,
                          "D:/C++/Nodest/Nodest/examples/tinyVectorPlayground/NodestVectorPlayground/Controls/Getters/");
    qmlRegisterType<NodeFactoryVector>("CppObjects", 1, 0, "NodeFactory");
    NodestGlobal::globalInit(&a);



    return a.exec();
}
