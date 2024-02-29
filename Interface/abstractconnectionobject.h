#pragma once

#include <QObject>
#include <QQuickItem>

namespace Nodest{

class Connection;
class AbstractExtension;

class AbstractConnectionObject : public QObject
{
    Q_OBJECT
public:
    explicit AbstractConnectionObject(QObject *parent = nullptr) : QObject(parent) {}

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
