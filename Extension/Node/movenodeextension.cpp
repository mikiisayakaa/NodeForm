#include "movenodeextension.h"


bool Nodest::MoveNodeExtension::addExtension(QQuickItem *signalSource)
{
    signalSource->setProperty("movable", true);
    return true;
}
