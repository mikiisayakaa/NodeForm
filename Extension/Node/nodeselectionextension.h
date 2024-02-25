#pragma once

#include <QObject>

#include "Extension/abstractextension.h"
#include "Extension/Graph/graphnodeselectionextension.h"

namespace Nodest{

class NodeSelectionExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit NodeSelectionExtension(QObject *parent = nullptr) :
        AbstractExtension(parent) { m_extensionName = "NodeSelection";}

    bool addExtension(QQuickItem* signalSource);

    bool checkDependency();

signals:

public slots:
    void onSelect();

private:
    GraphNodeSelectionExtension* m_graphSelectionExtension;
};

}
