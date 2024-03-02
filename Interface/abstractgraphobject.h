#pragma once

#include <QObject>
#include <QQuickItem>

#include "Core/abstractnodegraph.h"
#include "Core/connection.h"
#include "abstractnodeobject.h"

namespace Nodest{

class AbstractNodeGraph;
class AbstractExtension;
class AbstractConnectionObject;

class AbstractGraphObject : public QObject
{
    Q_OBJECT
public:
    explicit AbstractGraphObject(AbstractNodeGraph* graph, QObject *parent = nullptr);

    virtual ~AbstractGraphObject();

    void addNodeObject(AbstractNodeObject* nodeObj);

    virtual void createWidgets() = 0;

    int getNNode() const {return m_nodeObjects.size();}

    AbstractNodeObject* getNodeObject(int index) const {return m_nodeObjects[index];}

    int getNConnection() const {return m_connectionObjects.size();}

    AbstractConnectionObject* getConnectionObject(int index) const {return m_connectionObjects[index];}

    void reEvalSingle(AbstractNodeObject* nodeObj);

    AbstractConnectionObject* addSingleConnection(TestConnection* testConnection);

    void removeNodeObject(AbstractNodeObject* nodeObj);

    void removeSingleConnection(AbstractConnectionObject* connectionObject);

    QQuickItem* getBackground() const {return m_background;}

    AbstractNodeGraph* getGraph() const {return m_graph;}

    void copyNodeObj(AbstractNodeObject* nodeObj);

    void addExtension(AbstractExtension* extension);

    const std::vector<AbstractExtension*>& getExtensions() const {return m_extensions;}
signals:

public slots:


protected:


protected:
    AbstractNodeGraph* m_graph;

    std::vector<AbstractNodeObject*> m_nodeObjects;
    std::vector<AbstractConnectionObject*> m_connectionObjects;

    QQuickItem* m_background;

    std::vector<AbstractExtension*> m_extensions;
};

}
