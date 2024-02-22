#pragma once

#include <QObject>
#include <QQuickItem>

namespace Nodest{

class OutputSlot;

class AbstractSlotGetter : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSlotGetter(QObject *parent = nullptr): QObject(parent) {}

    virtual ~AbstractSlotGetter() {}

    void setSlot(OutputSlot* slot) {m_slot = slot;}

    void setItem(QQuickItem* item) {m_item = item;}

    void setTag(bool flag) {m_item->setProperty("valid", flag);}

    QString getTypeName() {return m_typeName;}

    virtual void sendValue() = 0;

signals:

public slots:

protected:
    OutputSlot* m_slot;

    QQuickItem* m_item;

    QString m_typeName;
};

}
