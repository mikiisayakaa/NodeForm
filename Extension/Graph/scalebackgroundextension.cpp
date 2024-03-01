#include "scalebackgroundextension.h"
#include "Interface/abstractgraphobject.h"

bool Nodest::ScaleBackgroundExtension::addExtension(QQuickItem *signalSource)
{
    connect(signalSource, SIGNAL(rescale()), this, SLOT(onRescale()));
    connect(signalSource, SIGNAL(stopRescale()), this, SLOT(onStopRescale()));
    return true;
}

void Nodest::ScaleBackgroundExtension::onRescale()
{
    QQuickItem* background = dynamic_cast<AbstractGraphObject*>(parent())->getBackground();
    background->setProperty("scalable", true);
}

void Nodest::ScaleBackgroundExtension::onStopRescale()
{
    QQuickItem* background = dynamic_cast<AbstractGraphObject*>(parent())->getBackground();
    background->setProperty("scalable", false);
}
