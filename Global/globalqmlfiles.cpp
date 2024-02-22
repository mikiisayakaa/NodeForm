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

QString backgroundFile = "Background.qml";
QQmlComponent* bgd;

QString lineFile = "Line3.qml";
QQmlComponent* connectionLine;
}
