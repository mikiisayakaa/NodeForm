#include "movebackgroundextension.h"
#include "Interface/abstractgraphobject.h"

bool Nodest::MoveBackgroundExtension::addExtension(QQuickItem *signalSource)
{
    connect(signalSource, SIGNAL(move()), this, SLOT(onMove()));
    connect(signalSource, SIGNAL(stopMove()), this, SLOT(onStopMove()));
    return true;
}

void Nodest::MoveBackgroundExtension::onMove()
{
    QQuickItem* background = dynamic_cast<AbstractGraphObject*>(parent())->getBackground();
    background->setProperty("movable", true);
}

void Nodest::MoveBackgroundExtension::onStopMove()
{
    QQuickItem* background = dynamic_cast<AbstractGraphObject*>(parent())->getBackground();
    background->setProperty("movable", false);
}
