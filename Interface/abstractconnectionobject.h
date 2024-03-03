#pragma once

#include <QObject>
#include <QQuickItem>

#include "Core/connection.h"

namespace Nodest{

class Connection;
class AbstractExtension;

class AbstractConnectionObject : public QObject
{
    Q_OBJECT
public:
    explicit AbstractConnectionObject(QObject *parent = nullptr) : QObject(parent),
    m_connectionItem(nullptr), m_connection(nullptr) {}

    virtual ~AbstractConnectionObject();

    void setItem(QQuickItem* connectionItem) {m_connectionItem = connectionItem;}
    QQuickItem* getItem() const {return m_connectionItem;}

    void setConnection(Connection* connection) {m_connection = connection;}
    Connection* getConnection() const {return m_connection;}

    void addExtension(AbstractExtension* extension);

    virtual void addExtensions() {}

signals:

public slots:

protected:
    QQuickItem* m_connectionItem;

    Connection* m_connection;

    std::vector<AbstractExtension*> m_extensions;

};

}
