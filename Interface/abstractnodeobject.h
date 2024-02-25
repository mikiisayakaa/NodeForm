#pragma once

#include "Core/abstractnode.h"
#include "Wrapper/abstractslotsetter.h"
#include "abstractslotobject.h"
#include "Extension/abstractextension.h"

#include <QObject>
#include <QQuickItem>

#include <vector>

namespace Nodest{

class AbstractNodeObject : public QObject
{
    Q_OBJECT
public:
    explicit AbstractNodeObject(AbstractNode* node, QObject *parent = nullptr);

    virtual void createWidgets() = 0;

    virtual void setWidgetsLayout() = 0;

    virtual void bindWidgets() = 0;

    virtual AbstractNodeObject* clone() = 0;

    AbstractNode* getNode() const {return m_node;}

    QQuickItem* getNodeBase() const {return m_nodeBase;}

    QQuickItem* getItem(int index) const {return m_items[index];}

    void addExtension(AbstractExtension* extension);

signals:

public slots:

protected:
    AbstractNode* m_node;

    QQuickItem* m_nodeBase;

    std::vector<QQuickItem*> m_items;

    std::vector<AbstractSlotObject*> m_inputObjects;
    std::vector<AbstractSlotObject*> m_outputObjects;

    std::vector<AbstractExtension*> m_extensions;
};

}
