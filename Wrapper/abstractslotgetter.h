#pragma once

#include <QObject>
#include <QQuickItem>

namespace NF{

class OutputSlot;

class AbstractSlotGetter : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSlotGetter(QObject *parent = nullptr): QObject(parent), m_item(nullptr) {}

    virtual ~AbstractSlotGetter() {}

    void setSlot(OutputSlot* slot) {m_slot = slot;}

    void setItem(QQuickItem* item) {m_item = item;}

    void setTag(bool flag) {if (m_item){m_item->setProperty("valid", flag);}}

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
