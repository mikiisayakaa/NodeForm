#pragma once

#include <QObject>

#include "Extension/abstractextension.h"

namespace Nodest{

class AbstractConnectionObject;

class GraphConnectionSelectionExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit GraphConnectionSelectionExtension(QObject *parent = nullptr) :
        AbstractExtension(parent) {m_extensionName = "GraphConnectionSelection";
                                   m_type = ExtensionType::GraphConnectionSelection;}

    bool addExtension(QQuickItem* signalSource);

    void selectOne(AbstractConnectionObject* connectObj);

    void deselectOne(AbstractConnectionObject* connectObj);

    std::vector<AbstractConnectionObject*>& getSelectedConnections() {return m_selectedConnections;}

signals:

public slots:

    void onDeselect();

private:
    std::vector<AbstractConnectionObject*> m_selectedConnections;
};

}
