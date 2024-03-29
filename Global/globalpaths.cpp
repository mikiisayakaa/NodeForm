#include "globalpaths.h"

namespace NF{

//folder contains all qml widgets to load
QStringList nodeJsonPaths = {};

QStringList globalJsonPaths = {qmlPath + "GlobalWidgets/"};

QStringList qmlHandlesPaths = {qmlPath + "Handles/"};

QStringList qmlDataBridgeGetterPaths = {qmlPath + "DataBridges/Getters/"};

QStringList qmlDataBridgeSetterPaths = {qmlPath + "DataBridges/Setters/"};

QStringList qmlTextLabelsPaths = {qmlPath + "TextLabels/"};

QStringList qmlNodeBasePaths = {qmlPath + "NodeBase/"};

QStringList qmlCurvePaths = {qmlPath + "GlobalWidgets/Curve/"};

QStringList qmlBackgroundPath = {qmlPath + "GlobalWidgets/Background/"};

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

