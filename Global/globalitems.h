#pragma once

#include <QObject>
#include <QQuickItem>
#include <QQmlApplicationEngine>

#include "Interface/abstractgraphobject.h"


namespace NF{

extern QQmlApplicationEngine* engine;

extern QQuickItem* globalRootObject;

extern QQuickItem* globalBackground;

extern NF::AbstractGraphObject* globalGraphObject;
}
