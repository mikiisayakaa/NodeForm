#include <QApplication>

#include "Global/globalinit.h"
#include "Global/globalpaths.h"

#include "Global/globalitems.h"

#include "nodefactoryimage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //get rid of annoying warnings caused by QML FileDialog
    QCoreApplication::setOrganizationName("NoOrganization");

    NodestGlobal::setPath(NodestGlobal::nodeJsonPaths,
                          "D:/C++/Nodest/Nodest/examples/tinyImageProcessor/NodestImageProcessor/UI/");
    NodestGlobal::setPath(NodestGlobal::qmlGettersPaths,
                          "D:/C++/Nodest/Nodest/examples/tinyImageProcessor/NodestImageProcessor/Controls/Getters/");
    NodestGlobal::setPath(NodestGlobal::qmlSettersPaths,
                          "D:/C++/Nodest/Nodest/examples/tinyImageProcessor/NodestImageProcessor/Controls/Setters/");
    NodestGlobal::setQmlMain("D:/C++/Nodest/Nodest/examples/tinyImageProcessor/NodestImageProcessor/Controls/main.qml");
    qmlRegisterType<NodeFactoryImage>("CppObjects", 1, 0, "NodeFactory");
    NodestGlobal::globalInit(&a);

    return a.exec();
}
