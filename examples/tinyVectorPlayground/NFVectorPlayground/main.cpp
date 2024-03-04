#include <QApplication>
#include <QDir>

#include "Global/globalinit.h"
#include "Global/globalpaths.h"

#include "Global/globalitems.h"

#include "nodefactoryvector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NF::setPath(NF::nodeJsonPaths, QDir::currentPath() + "/../NFVectorPlayground/UI/");
    NF::setPath(NF::qmlGettersPaths, QDir::currentPath() + "/../NFVectorPlayground/Controls/Getters/");
    NF::setQmlMain(QDir::currentPath() + "/../NFVectorPlayground/Controls/main.qml");
    qmlRegisterType<NodeFactoryVector>("CppObjects", 1, 0, "NodeFactory");
    NF::globalInit(&a);



    return a.exec();
}
