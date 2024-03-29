#pragma once

#include "globalqmlfiles.h"

#include <QString>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QHash>
#include <QSet>
#include <QApplication>

namespace NF{

//init functions

void prepareUIWidgets(QQmlEngine* engine);

void fillDummy(QQmlEngine* engine);

//void fillBackground(QQmlEngine* engine);

//void fillConnectionLine(QQmlEngine* engine);

//recursively traverse a folder to load all json files
void fillNodeUImap(const QString& path);
void fillGlobalUI(const QString& path);

void fillQmlData(const QString& path, QQmlEngine* engine, QHash<QString, QQmlComponent*>& mp);
void setQmlDefault(const QString& path, QString& defaultFile);

void fillQmlGSData(const QString&, QQmlEngine* engine, QHash<QString, setGetInfo>& mp);
void setQmlGSDefault(const QString& path, QSet<QString>& defaultFiles);

void fillQmlDataBridgeData(const QString& path, QQmlEngine* engine, QHash<QString, DataBridgeInfo>& mp);
void setQmlDataBridgeDefault(const QString& path, QSet<QString>& defaultFiles);

void globalInit(QApplication* app);



}
