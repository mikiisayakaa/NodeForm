
#include <QApplication>
#include <QDebug>

#include "Global/globalinit.h"
#include "Global/globalpaths.h"

#include "Global/globalitems.h"

#include "nodefactory.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NodestGlobal::setPath(NodestGlobal::nodeJsonPaths,
                          "D:/C++/Nodest/Nodest/examples/tinyCalculator/NodestCalculator/UI/");
    NodestGlobal::setQmlMain("D:/C++/Nodest/Nodest/examples/tinyCalculator/NodestCalculator/Controls/main.qml");
    qmlRegisterType<NodeFactory>("CppObjects", 1, 0, "NodeFactory");
    NodestGlobal::globalInit(&a);


    return a.exec();
}
