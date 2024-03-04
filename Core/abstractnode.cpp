#include "abstractnode.h"
#include "Interface/abstractnodeobject.h"

NF::AbstractNode::~AbstractNode()
{
    delete m_nodeObject;
}

void NF::AbstractNode::setGetterValidTag(bool tag)
{
    for (size_t i = 0; i < m_outputSlots.size(); i++){
        if (m_outputSlots[i]->getGetter()){
            m_outputSlots[i]->getGetter()->setTag(tag);
        }
    }
}

void NF::AbstractNode::addDepend(int num)
{
    bool preDependency = independent();
    m_dependencyCount += num;
    if (independent() != preDependency){
        setGetterValidTag(independent());
    }
}

void NF::AbstractNode::decDepend(int num)
{
    bool preDependency = independent();
    m_dependencyCount -= num;
    if (independent() != preDependency){
        setGetterValidTag(independent());
    }
}
