#pragma once

#include "abstractnode.h"
#include "abstractnodegraph.h"
#include "connection.h"

#include <QHash>

#include <queue>
#include <stack>

namespace Nodest{

class AbstractNode;

class BasicNodeGraph : public AbstractNodeGraph
{
public:
    explicit BasicNodeGraph() {}

    void addNode(AbstractNode* node);

    Connection* addSingleConnection(TestConnection* testConnection);

    void removeSingleConnection(Connection* connection);

    void removeNode(AbstractNode* node);

    void reEvalSingle(AbstractNode* node);

private:
    void eval();

    void clearAllTags();

    //we can only add one connection at a time
    bool checkConnection(TestConnection* testConnection);

    //check if a new connection will lead to cycles in the graph
    bool checkCyclic(TestConnection* testConnection);

    void clearDepth();

    void getDepth();

    void tagChildren(AbstractNode* node);

    void addChildrenToQueue(AbstractNode* node);

    //simple remove
    void removeConnection(Connection* connection);

    //must be called after validation check of the connection
    Connection* addConnection(OutputSlot* first, InputSlot* second);

private:
    std::vector<AbstractNode*> m_nodes;

    //used for subgraph evaluation
    QHash<AbstractNode*, int> m_depthMap;

    //assistant data structure for traverse
    std::queue<AbstractNode*> m_nodeQueue;
    std::stack<AbstractNode*> m_nodeStack;

};

}
