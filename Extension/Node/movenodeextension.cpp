#include "movenodeextension.h"


bool NF::MoveNodeExtension::addExtension(QQuickItem *signalSource)
{
    signalSource->setProperty("movable", true);
    return true;
}
