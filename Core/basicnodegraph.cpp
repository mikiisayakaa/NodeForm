#include "basicnodegraph.h"

#include "inputslot.h"
#include "outputslot.h"


void NF::BasicNodeGraph::addNode(NF::AbstractNode *node)
{
    m_nodes.push_back(node);
    addNodeToList(node);
    m_depthMap[node] = 0;

    if(node->independent()){
        //node->setGetterValidTag(true);
        node->eval();
    }
}

void NF::BasicNodeGraph::clearAllTags()
{
    for (auto node: m_nodes){
        node->clearTag();
    }
}


void NF::BasicNodeGraph::eval()
{
    //use depth data, should be calculated before
    std::vector<AbstractNode*> nodes;
    nodes.reserve(m_nodes.size());

    for (auto iter = m_depthMap.begin(); iter != m_depthMap.end(); iter++){
        //double check dependency here, mainly for node deletion,
        //we need to calculate depth before deletion
        if (iter.value() > 0 && iter.key()->independent()){
            size_t i = 0;
            for ( ; i < nodes.size(); i++){
                if (m_depthMap[nodes[i]] > iter.value()){
                    break;
                }
            }
            nodes.insert(nodes.begin() + i, iter.key());
        }
    }

    for (size_t i = 0; i < nodes.size(); i++){
        nodes[i]->eval();
        qDebug() << "Evaled:" << nodes[i]->getNameID();
    }
}

bool NF::BasicNodeGraph::checkCyclic(NF::TestConnection* testConnection)
{
    //simply check if connection's second has an existing path to first
    AbstractNode* start = testConnection->secondNode;
    AbstractNode* end = testConnection->firstNode;

    clearAllTags();
    m_nodeQueue.push(start);

    while(!m_nodeQueue.empty()){
        AbstractNode* curNode = m_nodeQueue.front();
        m_nodeQueue.pop();

        if (curNode == end){
            //clear the queue
            m_nodeQueue = std::queue<AbstractNode*>();
            return true;
        }

        if (curNode->tagged()){
            continue;
        }
        else{
            curNode->setTag();
        }

        addChildrenToQueue(curNode);
    }

    return false;
}

bool NF::BasicNodeGraph::checkConnection(NF::TestConnection* testConnection)
{
    //cannot connect input to input / output to output
    if (testConnection->firstFlow == testConnection->secondFlow){
        return false;
    }

    //cannot make a cycle in the graph
    if (checkCyclic(testConnection)){
        return false;
    }


    OutputSlot* first = testConnection->firstNode->getOutput(testConnection->firstIndex);
    InputSlot* second = testConnection->secondNode->getInput(testConnection->secondIndex);

    //cannot connect slots with different data types
    if (first->getTypeID() != second->getTypeID()){
        return false;
    }

    //cannot make duplicate connections
    if (second->getConnection() != nullptr && second->getConnection()->getFirst() == first){
        return false;
    }

    return true;
}

NF::Connection* NF::BasicNodeGraph::addSingleConnection(NF::TestConnection* testConnection)
{
    if (!checkConnection(testConnection)){
        return nullptr;
    }

    OutputSlot* first = testConnection->firstNode->getOutput(testConnection->firstIndex);
    InputSlot* second = testConnection->secondNode->getInput(testConnection->secondIndex);

    //if it already has a connection, remove it first
    if (second->getConnection() != nullptr){
        removeConnection(second->getConnection());
    }

    Connection* connection = addConnection(first, second);

    AbstractNode* node = second->getParent();
    reEvalSingle(node);

    return connection;
}

void NF::BasicNodeGraph::removeConnection(NF::Connection *connection)
{
    OutputSlot* first = connection->getFirst();
    InputSlot* second = connection->getSecond();
    first->removeConnection(connection);
    second->removeConnection(connection);

    removeConnectionFromList(connection);

    int depCount = first->getParent()->getDependency();
    if (second->getObj()->getDataBridge() == nullptr){
        //erase the dependency of the empty slot
        depCount -= 1;
    }

    if (depCount != 0){
        m_nodeQueue.push(second->getParent());
        clearAllTags();
        while(!m_nodeQueue.empty()){
            AbstractNode* curNode = m_nodeQueue.front();
            m_nodeQueue.pop();

            curNode->decDepend(depCount);

            if (curNode->tagged()){
                continue;
            }
            else{
                curNode->setTag();
            }

            addChildrenToQueue(curNode);
        }
    }

    delete connection;
}

NF::Connection* NF::BasicNodeGraph::addConnection(NF::OutputSlot *first, NF::InputSlot *second)
{
    Connection* connection = new Connection(first, second);
    first->setConnection(connection);
    second->setConnection(connection);

    int depCount = first->getParent()->getDependency();
    if (second->getObj()->getDataBridge() == nullptr){
        //erase the dependency of the empty slot
        depCount -= 1;
    }

    if (depCount != 0){
        m_nodeQueue.push(second->getParent());
        clearAllTags();
        while(!m_nodeQueue.empty()){
            AbstractNode* curNode = m_nodeQueue.front();
            m_nodeQueue.pop();

            curNode->addDepend(depCount);

            if (curNode->tagged()){
                continue;
            }
            else{
                curNode->setTag();
            }

            addChildrenToQueue(curNode);
        }
    }

    addConnectionToList(connection);

    return connection;
}


void NF::BasicNodeGraph::removeSingleConnection(NF::Connection *connection)
{
    AbstractNode* node = connection->getSecond()->getParent();
    removeConnection(connection);

    reEvalSingle(node);

}

void NF::BasicNodeGraph::removeNode(NF::AbstractNode *node)
{
    clearDepth();

    removeNodeFromList(node);

    for (size_t i = 0; i < m_nodes.size(); i++){
        if (node == m_nodes[i]){
            m_depthMap.remove(node);
            m_nodes.erase(m_nodes.begin() + i);
            break;
        }
    }

    //remove output connections
    for (size_t i = 0; i < node->getNOutput(); i++){
        OutputSlot* out = node->getOutput(i);
        //note that getNConnection()'s return value will change during loop

        while(out->getNConnection() != 0){
            Connection* connection = out->getConnection(0);
            AbstractNode* node = connection->getSecond()->getParent();
            removeConnection(connection);
            m_depthMap[node] = 1;
            m_NFack.push(node);
        }
    }

    //remove input connections
    for (size_t i = 0; i < node->getNInput(); i++){
        InputSlot* in = node->getInput(i);
        if (in->getConnection()){
            removeConnection(in->getConnection());
        }
    }

    delete node;

    getDepth();
    eval();
}

void NF::BasicNodeGraph::reEvalSingle(NF::AbstractNode *node)
{
    if (node->independent()){
        clearDepth();
        m_depthMap[node] = 1;
        m_NFack.push(node);
        getDepth();
        eval();
    }
}

void NF::BasicNodeGraph::clearDepth()
{
    for (auto iter = m_depthMap.begin(); iter != m_depthMap.end(); iter++){
        iter.value() = 0;
    }
}

void NF::BasicNodeGraph::getDepth()
{
    //DFS, maybe slower than topological sort, but easy to implement at local graph
    while(!m_NFack.empty()){
        AbstractNode* curNode = m_NFack.top();
        m_NFack.pop();

        for (size_t i = 0; i < curNode->getNOutput(); i++){
            OutputSlot* out = curNode->getOutput(i);
            for (size_t j = 0; j < out->getNConnection(); j++){
                AbstractNode* child = out->getConnection(j)->getSecond()->getParent();

                if (child->independent() && m_depthMap[child] < m_depthMap[curNode] + 1){
                    m_depthMap[child] = m_depthMap[curNode] + 1;
                    m_NFack.push(child);
                }
            }
        }
    }
}

//bool NF::BasicNodeGraph::checkUpstreamOutValid(NF::AbstractNode *node)
//{
//    bool rst = true;
//    for (size_t i = 0; i < node->getNInput(); i++){
//        InputSlot* slot = node->getInput(i);
//        if (slot->getConnection() != nullptr){
//            rst &= slot->getConnection()->getFirst()->getParent()->isOutValid();
//        }
//    }

//    return rst;
//}



void NF::BasicNodeGraph::addChildrenToQueue(NF::AbstractNode *node)
{
    for (size_t i = 0; i < node->getNOutput(); i++){
        OutputSlot* out = node->getOutput(i);
        for (size_t j = 0; j < out->getNConnection(); j++){
            AbstractNode* child = out->getConnection(j)->getSecond()->getParent();
            m_nodeQueue.push(child);
        }
    }
}
