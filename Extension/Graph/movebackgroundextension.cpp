#include "movebackgroundextension.h"
#include "Interface/abstractgraphobject.h"

bool NF::MoveBackgroundExtension::addExtension(QQuickItem *signalSource)
{
    connect(signalSource, SIGNAL(move()), this, SLOT(onMove()));
    connect(signalSource, SIGNAL(stopMove()), this, SLOT(onStopMove()));
    return true;
}

void NF::MoveBackgroundExtension::onMove()
{
    QQuickItem* background = dynamic_cast<AbstractGraphObject*>(parent())->getBackground();
    background->setProperty("movable", true);
}

void NF::MoveBackgroundExtension::onStopMove()
{
    QQuickItem* background = dynamic_cast<AbstractGraphObject*>(parent())->getBackground();
    background->setProperty("movable", false);
}
