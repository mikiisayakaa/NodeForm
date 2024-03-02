#pragma once

#include <QObject>

#include "Extension/abstractextension.h"

namespace Nodest{

class TestConnection;
class AbstractConnectionObject;

class DragAddExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit DragAddExtension(QObject *parent = nullptr);

    bool addExtension(QQuickItem* signalSource);

signals:

public slots:
    void onConnectionEnd(qreal x, qreal y);
    void onConnectionDrag(qreal x, qreal y);

private:
    void connectionStartHelper(QQuickItem* handle);

    QQuickItem* getBackground();

private:
    QQuickItem* m_handle;
    TestConnection* m_testConnection;
    AbstractConnectionObject* m_tempConnection;
};

}
