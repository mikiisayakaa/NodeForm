#pragma once

#include <QQuickItem>
#include <QQmlComponent>


namespace NF{

class AbstractSlot;
class InputSlot;
class OutputSlot;
class AbstractDataBridge;

//for creation functions below, caller should guarantee that
//the filename exists in the corresponding hashmap
void createTextLabel(const QString& fileName, QQuickItem* parentItem, QQuickItem*& target,
                     const QString& text);

void createHandle(const QString& fileName, QQuickItem* parentItem, QQuickItem*& target,
                  AbstractSlot* slot);

void createDummy(QQuickItem* parentItem, QQuickItem* &target);

void setLineHandle(QQuickItem* line, QQuickItem* handle);

void createDataBridge(const QString& fileName, QQuickItem* parentItem,
                      QQuickItem*& target, AbstractDataBridge* dataBridge, int flow);

void createBase(const QString& fileName, QQuickItem* parentItem, QQuickItem*& target);

void getValidDataBridgeFileName(QString& queryName, AbstractSlot* slot);

void setAnchors(QQuickItem *target, QQuickItem *source, const char *pos1, const char *pos2);
}
