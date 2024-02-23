#include <QApplication>
#include <QDebug>
#include <QHash>

#include "Global/globalinit.h"

#include "Global/typenamemacro.h"
#include "Global/typenameregistry.h"
#include "Global/globalitems.h"

#include "Interface/verticalnodeobject.h"
#include "Interface/basicgraphobject.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    NodestGlobal::globalInit(&app);

    return app.exec();
}
