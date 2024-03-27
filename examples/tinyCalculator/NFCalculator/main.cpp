
#include <QApplication>
#include <QDebug>
#include <QDir>

#include "Global/globalinit.h"
#include "Global/globalpaths.h"

#include "Global/globalitems.h"

#include "Extension/abstractextension.h"
#include "Extension/Graph/deleteselectednodeextension.h"
#include "Extension/Node/nodeselectionextension.h"

#include "nodefactory.h"
#include "typedefines.h"

#include "Utils/variant.h"
#include <iostream>

#include "Core/basicnodemacro.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NF::setPath(NF::nodeJsonPaths, QDir::currentPath() + "/../NFCalculator/UI/");
    NF::setQmlMain(QDir::currentPath() + "/../NFCalculator/Controls/main.qml");
    qmlRegisterType<NodeFactory>("CppObjects", 1, 0, "NodeFactory");
    NF::globalInit(&a);

    return a.exec();
}
