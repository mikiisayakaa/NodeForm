#pragma once

#include <QObject>

#include "Extension/abstractextension.h"
#include "Extension/Graph/graphconnectionselectionextension.h"

namespace Nodest{

class ConnectionSelectionExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit ConnectionSelectionExtension(QObject *parent = nullptr) :
        AbstractExtension(parent) {m_extensionName = "ConnectionSelection";}

    bool addExtension(QQuickItem* signalSource);

    bool checkDependency();

signals:

public slots:

    void onSelect();

private:
    GraphConnectionSelectionExtension* m_graphSelectionExtension;
};

}
