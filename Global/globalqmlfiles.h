#pragma once

#include <QString>
#include <QByteArray>
#include <QHash>
#include <QSet>
#include <QQmlComponent>

#include <vector>
#include <utility>

namespace NF{

struct setGetInfo{
    QQmlComponent* data;
    QString typeName;
};

struct DataBridgeInfo{
    QQmlComponent* data;
    QString cppTypeName;
    QString qmlTypeName;
};

extern QSet<QString> qmlFileNames;

extern QString slotHandleDefault;
extern QHash<QString, QQmlComponent*> slotHandleMap;

extern QSet<QString> dataBridgeDefault;
extern QHash<QString, DataBridgeInfo> dataBridgeMap;

extern QSet<QString> dataBridgeGetterDefault;
extern QHash<QString, DataBridgeInfo> dataBridgeGetterMap;

extern QSet<QString> dataBridgeSetterDefault;
extern QHash<QString, DataBridgeInfo> dataBridgeSetterMap;

extern QString textLabelDefault;
extern QHash<QString, QQmlComponent*> textLabelMap;

extern QString nodeBaseDefault;
extern QHash<QString, QQmlComponent*> nodeBaseMap;

//used to take a place for missing components
extern QString dummyFile;
extern QQmlComponent* dummy;


extern QString backgroundDefault;
extern QHash<QString, QQmlComponent*> backgroundMap;
//global background Rectangle for the node editor
//extern QString backgroundFile;
//extern QQmlComponent* bgd;
//void setBackgroundFile(const QString& filePath);

extern QString curveDefault;
extern QHash<QString, QQmlComponent*> curveMap;
//extern QString lineFile;
//extern QQmlComponent* connectionLine;
//void setLineFile(const QString& filePath);


}
