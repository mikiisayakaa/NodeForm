#include "globalpaths.h"

namespace NodestGlobal{

//folder contains all qml widgets to load
QStringList nodeJsonPaths = {};

QStringList qmlHandlesPaths = {qmlPath + "Handles/"};

QStringList qmlSettersPaths = {qmlPath + "Setters/"};

QStringList qmlGettersPaths = {qmlPath + "Getters/"};

QStringList qmlTextLabelsPaths = {qmlPath + "TextLabels/"};

QStringList qmlNodeBasePaths = {qmlPath + "NodeBase/"};

QString qmlMainPath = uiPath + "main.qml";

void setPath(QStringList &target, const QString &path)
{
    target.push_back(path);
}

void setQmlMain(const QString &path)
{
    qmlMainPath = path;
}


}

