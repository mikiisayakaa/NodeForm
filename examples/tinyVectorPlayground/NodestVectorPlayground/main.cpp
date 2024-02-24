#include <QApplication>
#include <QDir>

#include "Global/globalinit.h"
#include "Global/globalpaths.h"

#include "Global/globalitems.h"

#include "nodefactoryvector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NodestGlobal::setPath(NodestGlobal::nodeJsonPaths, QDir::currentPath() + "/../NodestVectorPlayground/UI/");
    NodestGlobal::setPath(NodestGlobal::qmlGettersPaths, QDir::currentPath() + "/../NodestVectorPlayground/Controls/Getters/");
    NodestGlobal::setQmlMain(QDir::currentPath() + "/../NodestVectorPlayground/Controls/main.qml");
    qmlRegisterType<NodeFactoryVector>("CppObjects", 1, 0, "NodeFactory");
    NodestGlobal::globalInit(&a);



    return a.exec();
}
