#pragma once

#include <QObject>

#include "Extension/abstractextension.h"

namespace NF{

class MoveNodeExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit MoveNodeExtension(QObject *parent = nullptr) :
        AbstractExtension(parent) {m_extensionName = "MoveNode";
                                   m_type = ExtensionType::MoveNode;}

    bool addExtension(QQuickItem* signalSource);

signals:

public slots:
};

}
