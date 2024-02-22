#pragma once

#include <QObject>
#include <QQuickItem>
#include <QQmlApplicationEngine>

#include "Interface/abstractgraphobject.h"


namespace NodestGlobal{

extern QQmlApplicationEngine* engine;

extern QQuickItem* globalRootObject;

extern QQuickItem* globalBackground;

extern Nodest::AbstractGraphObject* globalGraphObject;
}
