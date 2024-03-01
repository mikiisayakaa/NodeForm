#pragma once

#include <QObject>

#include "Extension/abstractextension.h"

namespace Nodest{

class ScaleBackgroundExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit ScaleBackgroundExtension(QObject *parent = nullptr) :
        AbstractExtension(parent) {m_extensionName = "ScaleBackground";
                                   m_type = ExtensionType::ScaleBackground;}

    bool addExtension(QQuickItem* signalSource);

signals:

public slots:

    void onRescale();
    void onStopRescale();
};

}

