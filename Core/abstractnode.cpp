#include "abstractnode.h"


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
    m_dependencyCount += num;
    if (independent()){
        setGetterValidTag(true);
    }
}

void Nodest::AbstractNode::decDepend(int num)
{
    if (independent()){
        setGetterValidTag(false);
    }
    m_dependencyCount -= num;
}
