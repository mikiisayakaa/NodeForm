#pragma once

#include <QObject>
#include <QQuickItem>

#include "Core/abstractslot.h"

namespace NF{

class AbstractExtension;
class AbstractDataBridge;

class AbstractSlotObject : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSlotObject(AbstractSlot* slot, QObject *parent = nullptr);

    virtual ~AbstractSlotObject() {}

    virtual void createWidgets() = 0;

    virtual void setWidgetsLayout() = 0;

    void addExtension(AbstractExtension* extension);

    virtual void addExtensions() {}

    void setBridge(AbstractDataBridge* bridge) {m_bridge = bridge;}

    AbstractSlot* getSlot() const {return m_slot;}

    QQuickItem* getItem(int index) const {return m_items[index];}

signals:

public slots:

protected:
    AbstractSlot* m_slot;

    AbstractDataBridge* m_bridge;

    std::vector<QQuickItem*> m_items;

    std::vector<AbstractExtension*> m_extensions;
};

}
