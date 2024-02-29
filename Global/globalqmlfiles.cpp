#include "globalqmlfiles.h"

namespace NodestGlobal{

QSet<QString> qmlFileNames;

QString slotHandleDefault;
QHash<QString, QQmlComponent*> slotHandleMap;

//filename and setter id
QSet<QString> slotSetterDefault;
QHash<QString, setGetInfo> slotSetterMap;

QSet<QString> slotGetterDefault;
QHash<QString, setGetInfo> slotGetterMap;

QString textLabelDefault;
QHash<QString, QQmlComponent*> textLabelMap;

QString nodeBaseDefault;
QHash<QString, QQmlComponent*> nodeBaseMap;

QString dummyFile = "dummy.qml";
QQmlComponent* dummy;

QString curveDefault;
QHash<QString, QQmlComponent*> curveMap;

QString backgroundDefault;
QHash<QString, QQmlComponent*> backgroundMap;

//QString backgroundFile = "NodestBackground1.qml";
//QQmlComponent* bgd;

//QString lineFile = "NodestBezierCurve2.qml";
//QQmlComponent* connectionLine;

//void setBackgroundFile(const QString &filePath)
//{
//    backgroundFile = filePath;
//}

//void setLineFile(const QString &filePath)
//{
//    lineFile = filePath;
//}

}
