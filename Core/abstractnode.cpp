#include "abstractnode.h"
#include "Interface/abstractnodeobject.h"

void Nodest::AbstractNode::setGetterValidTag(bool tag)
{
    for (size_t i = 0; i < m_outputSlots.size(); i++){
        if (m_outputSlots[i]->getGetter()){
            m_outputSlots[i]->getGetter()->setTag(tag);
        }
    }
}

void Nodest::AbstractNode::addDepend(int num)
{
    bool preDependency = independent();
    m_dependencyCount += num;
    if (independent() != preDependency){
        setGetterValidTag(independent());
    }
}

void Nodest::AbstractNode::decDepend(int num)
{
    bool preDependency = independent();
    m_dependencyCount -= num;
    if (independent() != preDependency){
        setGetterValidTag(independent());
    }
}
