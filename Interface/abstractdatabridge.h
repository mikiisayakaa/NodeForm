#pragma once

#include <QObject>
#include <QQuickItem>

namespace NF{

class AbstractSlot;

class AbstractDataBridge : public QObject
{
    Q_OBJECT
public:
    explicit AbstractDataBridge(QObject *parent = nullptr) : QObject(parent) {}

    //must setSlot befor setItem
    void setSlot(AbstractSlot* slot) {m_slot = slot;}

    void setItem(QQuickItem* item) {m_item = item;};

    QQuickItem* getItem() const {return m_item;}

    virtual void bind() = 0;


signals:

public slots:

protected:
    AbstractSlot* m_slot;

    QQuickItem* m_item;
};

}
