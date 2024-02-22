#pragma once

#include "abstractnode.h"
#include "connection.h"
#include "Interface/abstractgraphobject.h"

namespace Nodest{

class AbstractGraphObject;

class AbstractNodeGraph
{
public:
    AbstractNodeGraph() = default;

    virtual ~AbstractNodeGraph() {}

    virtual void addNode(AbstractNode* node) = 0;

    virtual Connection* addSingleConnection(TestConnection* testConnection) = 0;

    virtual void removeSingleConnection(Connection* connection) = 0;

    virtual void removeNode(AbstractNode* node) = 0;

    virtual void reEvalSingle(AbstractNode* node) = 0;

    void setObj(AbstractGraphObject* graphObj) {m_graphObject = graphObj;}
    AbstractGraphObject* getObj() const {return m_graphObject;}

protected:
    AbstractGraphObject* m_graphObject;
};

}
