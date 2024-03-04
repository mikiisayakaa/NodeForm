#pragma once

#include <QObject>

#include "Extension/Slot/dragaddconnectionextension.h"

namespace NF{

class InDragAddConnectionExtension : public DragAddConnectionExtension
{
    Q_OBJECT
public:
    explicit InDragAddConnectionExtension(QObject *parent = nullptr);

    bool addExtension(QQuickItem* signalSource);

signals:

public slots:
    void onConnectionDrag(qreal x, qreal y);
};

}
