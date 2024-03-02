#pragma once

#include <QObject>

#include "Extension/Slot/dragaddconnectionextension.h"

namespace Nodest{

class TestConnection;
class AbstractConnectionObject;

class OutDragAddConnectionExtension : public DragAddConnectionExtension
{
    Q_OBJECT
public:
    explicit OutDragAddConnectionExtension(QObject *parent = nullptr);

    bool addExtension(QQuickItem* signalSource);

signals:

public slots:
    void onConnectionDrag(qreal x, qreal y);


};

}
