#pragma once

#include <QQuickItem>
#include <QQmlComponent>


namespace Nodest{

class AbstractSlot;
class InputSlot;
class OutputSlot;

//for creation functions below, caller should guarantee that
//the filename exists in the corresponding hashmap
void createTextLabel(const QString& fileName, QQuickItem* parentItem, QQuickItem*& target,
                     const QString& text);

void createHandle(const QString& fileName, QQuickItem* parentItem, QQuickItem*& target,
                  AbstractSlot* slot);

void setLinePoint(QQuickItem* line, QQuickItem* handle);

void createSetter(const QString& fileName, QQuickItem* parentItem, QQuickItem*& target,
                  AbstractSlot* slot);

void createGetter(const QString& fileName, QQuickItem* parentItem, QQuickItem*& target,
                  OutputSlot* slot);

void createBase(const QString& fileName, QQuickItem* parentItem, QQuickItem*& target);

void getValidSetterFileName(QString& queryName, InputSlot* slot);

void getValidGetterFileName(QString& queryName, OutputSlot* slot);

void setAnchors(QQuickItem *target, QQuickItem *source, const char *pos1, const char *pos2);
}
