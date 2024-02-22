
#include <QApplication>
#include <QDebug>

#include "Global/globalinit.h"
#include "Global/globalpaths.h"

#include "Global/globalitems.h"

#include "nodefactory.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NodestGlobal::setPath(NodestGlobal::nodeJsonPath,
                          "D:/C++/Nodest/Nodest/examples/tinyCalculator/NodestCalculator/UI/");
    NodestGlobal::setPath(NodestGlobal::qmlMainPath,
                          "D:/C++/Nodest/Nodest/examples/tinyCalculator/NodestCalculator/Controls/");
    qmlRegisterType<NodeFactory>("CppObjects", 1, 0, "NodeFactory");
    NodestGlobal::globalInit(&a);


    return a.exec();
}
