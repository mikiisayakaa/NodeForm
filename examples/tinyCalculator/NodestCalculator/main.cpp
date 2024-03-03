
#include <QApplication>
#include <QDebug>
#include <QDir>

#include "Global/globalinit.h"
#include "Global/globalpaths.h"

#include "Global/globalitems.h"

#include "nodefactory.h"
#include "typedefines.h"

#include "Utils/variant.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Nodest::Variant* var = Nodest::Variant::createVariant<int>(5);
//    var->set<char>('v');

    NodestGlobal::setPath(NodestGlobal::nodeJsonPaths, QDir::currentPath() + "/..NodestCalculator/UI/");
    NodestGlobal::setQmlMain(QDir::currentPath() + "/../NodestCalculator/Controls/main.qml");
    qmlRegisterType<NodeFactory>("CppObjects", 1, 0, "NodeFactory");
    NodestGlobal::globalInit(&a);


    return a.exec();
}
