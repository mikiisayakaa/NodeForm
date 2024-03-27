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

    NF::setPath(NF::nodeJsonPaths, QDir::currentPath() + "/../NFImageProcessor/UI/");
    NF::setPath(NF::qmlDataBridgeGetterPaths, QDir::currentPath() + "/../NFImageProcessor/Controls/Getters/");
    NF::setPath(NF::qmlDataBridgeSetterPaths, QDir::currentPath() + "/../NFImageProcessor/Controls/Setters/");
    NF::setQmlMain(QDir::currentPath() + "/../NFImageProcessor/Controls/main.qml");
    qmlRegisterType<NodeFactoryImage>("CppObjects", 1, 0, "NodeFactory");
    NF::globalInit(&a);

    return a.exec();
}
