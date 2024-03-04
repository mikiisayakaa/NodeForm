#include "abstractevalnode.h"


void NF::AbstractEvalNode::setSlotParent(NF::AbstractEvalNode* parent)
{
    for (auto slot : m_inputSlots){
        slot->setParent(parent);
    }
    for (auto slot : m_outputSlots){
        slot->setParent(parent);
    }
}
