#pragma once

#include <QObject>

#include "Extension/abstractextension.h"

namespace Nodest{

class TestConnection;
class AbstractConnectionObject;

class DragAddConnectionExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit DragAddConnectionExtension(QObject *parent = nullptr) :
        AbstractExtension(parent), m_testConnection(nullptr), m_tempConnection(nullptr) {}

signals:

public slots:
    void onConnectionEnd(qreal x, qreal y);

protected:
    void connectionStartHelper(QQuickItem* handle);

    QQuickItem* getBackground();

protected:
    QQuickItem* m_handle;
    TestConnection* m_testConnection;
    AbstractConnectionObject* m_tempConnection;
};

}
