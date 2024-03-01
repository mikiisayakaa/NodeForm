#pragma once

#include <QObject>

#include "Extension/abstractextension.h"

namespace Nodest{

class MoveBackgroundExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit MoveBackgroundExtension(QObject *parent = nullptr) :
        AbstractExtension(parent) {m_extensionName = "MoveBackground";
                                   m_type = ExtensionType::MoveBackground;}

    bool addExtension(QQuickItem* signalSource);

signals:

public slots:
    void onMove();
    void onStopMove();
};

}
