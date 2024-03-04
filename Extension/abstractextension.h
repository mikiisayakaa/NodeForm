#pragma once

#include <QObject>
#include <QQuickItem>

#include "extensiontypes.h"

namespace NF{

class AbstractExtension : public QObject
{
    Q_OBJECT
public:
    explicit AbstractExtension(QObject *parent = nullptr): QObject(parent) {}

    virtual ~AbstractExtension() {}

    virtual bool addExtension(QQuickItem* signalSource) = 0;

    virtual bool checkDependency() {return true;}

    QString getExtensionName() {return m_extensionName;}

    ExtensionType getExtensionType() {return m_type;}

signals:

public slots:

protected:
    QString m_extensionName;

    ExtensionType m_type;
    AbstractExtension* m_parentExtension;
};

}
