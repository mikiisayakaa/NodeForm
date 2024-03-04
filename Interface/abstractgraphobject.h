#pragma once

#include <QObject>
#include <QQuickItem>

#include "Core/abstractnodegraph.h"
#include "Core/connection.h"
#include "abstractnodeobject.h"

namespace NF{

class AbstractNodeGraph;
class AbstractExtension;
class AbstractConnectionObject;

class AbstractGraphObject : public QObject
{
    Q_OBJECT
public:
    explicit AbstractGraphObject(AbstractNodeGraph* graph, QObject *parent = nullptr);

    virtual ~AbstractGraphObject() {};

    void addNodeObject(AbstractNodeObject* nodeObj);

    virtual void createWidgets() = 0;

    int getNNode() const {return m_graph->getNodes().size();}

    AbstractNodeObject* getNodeObject(int index) const {return m_graph->getNodes()[index]->getObj();}

    int getNConnection() const {return m_graph->getConnections().size();}

    AbstractConnectionObject* getConnectionObject(int index) const {return m_graph->getConnections()[index]->getObj();}

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

    QQuickItem* m_background;

    std::vector<AbstractExtension*> m_extensions;
};

}
