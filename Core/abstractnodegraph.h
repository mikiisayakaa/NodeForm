#pragma once

#include <vector>

namespace NF{

class AbstractGraphObject;
class AbstractNode;
class Connection;
class TestConnection;

class AbstractNodeGraph
{
public:
    AbstractNodeGraph() = default;

    virtual ~AbstractNodeGraph();

    virtual void addNode(AbstractNode* node) = 0;

    virtual Connection* addSingleConnection(TestConnection* testConnection) = 0;

    virtual void removeSingleConnection(Connection* connection) = 0;

    virtual void removeNode(AbstractNode* node) = 0;

    virtual void reEvalSingle(AbstractNode* node) = 0;

    void setObj(AbstractGraphObject* graphObj) {m_graphObject = graphObj;}
    AbstractGraphObject* getObj() const {return m_graphObject;}

    std::vector<AbstractNode*>& getNodes() {return m_nodes;}
    std::vector<Connection*>& getConnections() {return m_connections;}

protected:
    void addNodeToList(AbstractNode* node);

    void removeNodeFromList(AbstractNode* node);

    void addConnectionToList(Connection* connection);

    void removeConnectionFromList(Connection* connection);

protected:
    AbstractGraphObject* m_graphObject;

    std::vector<AbstractNode*> m_nodes;
    std::vector<Connection*> m_connections;
};

}
