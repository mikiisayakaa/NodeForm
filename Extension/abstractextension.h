#pragma once

#include <QObject>
#include <QQuickItem>

namespace Nodest{

class AbstractExtension : public QObject
{
    Q_OBJECT
public:
    explicit AbstractExtension(QObject *parent = nullptr): QObject(parent) {}

    virtual ~AbstractExtension() {}

    virtual bool addExtension(QQuickItem* signalSource) = 0;

    virtual bool checkDependency() {return true;}

    QString getExtensionName() {return m_extensionName;}

signals:

public slots:

protected:
    QString m_extensionName;

    AbstractExtension* m_parentExtension;
};

}
