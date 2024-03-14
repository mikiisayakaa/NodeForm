#include "abstractnode.h"
#include "Interface/abstractnodeobject.h"

NF::AbstractNode::~AbstractNode()
{
    delete m_nodeObject;
}


void NF::AbstractNode::addDepend(int num)
{
    bool preDependency = independent();
    m_dependencyCount += num;

}

void NF::AbstractNode::decDepend(int num)
{
    bool preDependency = independent();
    m_dependencyCount -= num;

}
