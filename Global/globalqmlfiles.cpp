#include "globalqmlfiles.h"

namespace NF{

QSet<QString> qmlFileNames;

QString slotHandleDefault;
QHash<QString, QQmlComponent*> slotHandleMap;

QSet<QString> dataBridgeDefault;
QHash<QString, DataBridgeInfo> dataBridgeMap;

QSet<QString> dataBridgeGetterDefault;
QHash<QString, DataBridgeInfo> dataBridgeGetterMap;

QSet<QString> dataBridgeSetterDefault;
QHash<QString, DataBridgeInfo> dataBridgeSetterMap;

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

//QString backgroundFile = "NFBackground1.qml";
//QQmlComponent* bgd;

//QString lineFile = "NFBezierCurve2.qml";
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
