#pragma once

#include <QObject>

#include "Extension/abstractextension.h"

namespace NF{

class TestConnection;
class AbstractConnectionObject;

class DragAddConnectionExtension : public AbstractExtension
{
    Q_OBJECT
public:
    explicit DragAddConnectionExtension(QObject *parent = nullptr) :
        AbstractExtension(parent), m_testConnection(nullptr) {}

signals:

public slots:
    void onConnectionEnd(qreal x, qreal y);

protected:
    void connectionStartHelper(QQuickItem* handle);

    QQuickItem* getBackground();

protected:
    QQuickItem* m_handle;

    //store the temporal curve qml widget during creation of a connection
    QQuickItem* m_line;
    TestConnection* m_testConnection;
};

}
