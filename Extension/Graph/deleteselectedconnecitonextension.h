#pragma once

#include <QObject>

#include "Extension/abstractextension.h"

namespace NF{

class GraphConnectionSelectionExtension;

class DeleteSelectedConnecitonExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit DeleteSelectedConnecitonExtension(QObject *parent = nullptr) :
        AbstractExtension(parent) {m_extensionName = "DeleteSelectedConnection";
                                   m_type = ExtensionType::DeleteSelectedConnection;}

    bool addExtension(QQuickItem* signalSource);

    bool checkDependency();

signals:

public slots:

    void onDelete();

private:
    GraphConnectionSelectionExtension* m_graphSelectionExtension;
};

}
