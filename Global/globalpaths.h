#pragma once

#include <QString>
#include <QStringList>
#include <QDir>

namespace NF{

static QString uiPath = QDir::currentPath() + "/../../../UI/";

static QString qmlPath = uiPath + "qmlWidgets/";

//we allow users to store qml files and json files in different folders
//but every qml folder should contain a default.json, or you'll have to
//specify qml file names every time you fill in a node's UI json file.
extern QStringList nodeJsonPaths;

extern QStringList globalJsonPaths;

extern QStringList qmlHandlesPaths;

extern QStringList qmlDataBridgeGetterPaths;

extern QStringList qmlDataBridgeSetterPaths;

extern QStringList qmlTextLabelsPaths;

extern QStringList qmlNodeBasePaths;

extern QStringList qmlCurvePaths;

extern QStringList qmlBackgroundPath;

extern QString qmlMainPath;

void setPath(QStringList& target, const QString& path);

void setQmlMain(const QString& path);
}
