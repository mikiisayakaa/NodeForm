#include <QApplication>
#include <QDir>

#include "Global/globalinit.h"
#include "Global/globalpaths.h"

#include "Global/globalitems.h"

#include "nodefactoryimage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //get rid of annoying warnings caused by QML FileDialog
    QCoreApplication::setOrganizationName("NoOrganization");

    NodestGlobal::setPath(NodestGlobal::nodeJsonPaths, QDir::currentPath() + "/../NodestImageProcessor/UI/");
    NodestGlobal::setPath(NodestGlobal::qmlGettersPaths, QDir::currentPath() + "/../NodestImageProcessor/Controls/Getters/");
    NodestGlobal::setPath(NodestGlobal::qmlSettersPaths, QDir::currentPath() + "/../NodestImageProcessor/Controls/Setters/");
    NodestGlobal::setQmlMain(QDir::currentPath() + "/../NodestImageProcessor/Controls/main.qml");
    qmlRegisterType<NodeFactoryImage>("CppObjects", 1, 0, "NodeFactory");
    NodestGlobal::globalInit(&a);

    return a.exec();
}
