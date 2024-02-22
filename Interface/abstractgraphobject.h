#pragma once

#include <QObject>
#include <QQuickItem>

#include "Core/abstractnodegraph.h"
#include "Core/connection.h"
#include "abstractnodeobject.h"
#include "Core/connection.h"

namespace Nodest{

class AbstractNodeGraph;

class AbstractGraphObject : public QObject
{
    Q_OBJECT
public:
    explicit AbstractGraphObject(AbstractNodeGraph* graph, QObject *parent = nullptr);

    virtual ~AbstractGraphObject();

    void addNodeObject(AbstractNodeObject* nodeObj);

    virtual void createWidgets() = 0;

    virtual void bindWidgets() = 0;

    int getNNodes() const {return m_nodeObjects.size();}

    AbstractNodeObject* getNodeObject(int index) const {return m_nodeObjects[index];}

    void reEvalSingle(AbstractNodeObject* nodeObj);

    Connection* addSingleConnection(TestConnection* testConnection);

    void removeNodeObject(AbstractNodeObject* nodeObj);

    void removeSingleConnection(ConnectionObject* connectionObject);

    QQuickItem* getBackground() const {return m_background;}

    AbstractNodeGraph* getGraph() const {return m_graph;}

    void copyNodeObj(AbstractNodeObject* nodeObj);

signals:

public slots:


protected:
    void removeObjectFromVector(AbstractNodeObject* nodeObj);

protected:
    AbstractNodeGraph* m_graph;

    std::vector<AbstractNodeObject*> m_nodeObjects;

    QQuickItem* m_background;
};

}
