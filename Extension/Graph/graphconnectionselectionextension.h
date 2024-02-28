#pragma once

#include <QObject>

#include "Extension/abstractextension.h"

namespace Nodest{

class ConnectionObject;

class GraphConnectionSelectionExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit GraphConnectionSelectionExtension(QObject *parent = nullptr) :
        AbstractExtension(parent) {m_extensionName = "GraphConnectionSelection";}

    bool addExtension(QQuickItem* signalSource);

    void selectOne(ConnectionObject* connectObj);

    void deselectOne(ConnectionObject* connectObj);


signals:

public slots:

    void onDeselect();

private:
    std::vector<ConnectionObject*> m_selectedConnections;
};

}
