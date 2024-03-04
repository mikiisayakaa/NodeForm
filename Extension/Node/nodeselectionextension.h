#pragma once

#include <QObject>
#include <QDebug>

#include "Extension/abstractextension.h"
#include "Extension/Graph/graphnodeselectionextension.h"

namespace NF{

class NodeSelectionExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit NodeSelectionExtension(QObject *parent = nullptr) :
        AbstractExtension(parent) { m_extensionName = "NodeSelection";
                                    m_type = ExtensionType::NodeSelection;}

    bool addExtension(QQuickItem* signalSource);

    bool checkDependency();

signals:

public slots:
    void onSelect();

private:
    GraphNodeSelectionExtension* m_graphSelectionExtension;
};

}
