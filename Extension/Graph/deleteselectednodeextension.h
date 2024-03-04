#pragma once

#include <QObject>

#include "Extension/abstractextension.h"

namespace NF{

class GraphNodeSelectionExtension;

class DeleteSelectedNodeExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit DeleteSelectedNodeExtension(QObject *parent = nullptr) :
        AbstractExtension(parent) {m_extensionName = "DeleteSelectedNode";
                                   m_type = ExtensionType::DeleteSelectedNode;}

    bool addExtension(QQuickItem* signalSource);

    bool checkDependency();

signals:

public slots:

    void onDelete();

private:
    GraphNodeSelectionExtension* m_graphSelectionExtension;
};

}

