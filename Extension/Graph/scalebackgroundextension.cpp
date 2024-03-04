#include "scalebackgroundextension.h"
#include "Interface/abstractgraphobject.h"

bool NF::ScaleBackgroundExtension::addExtension(QQuickItem *signalSource)
{
    connect(signalSource, SIGNAL(rescale()), this, SLOT(onRescale()));
    connect(signalSource, SIGNAL(stopRescale()), this, SLOT(onStopRescale()));
    return true;
}

void NF::ScaleBackgroundExtension::onRescale()
{
    QQuickItem* background = dynamic_cast<AbstractGraphObject*>(parent())->getBackground();
    background->setProperty("scalable", true);
}

void NF::ScaleBackgroundExtension::onStopRescale()
{
    QQuickItem* background = dynamic_cast<AbstractGraphObject*>(parent())->getBackground();
    background->setProperty("scalable", false);
}
