#include "abstractevalnode.h"


void Nodest::AbstractEvalNode::setSlotParent(Nodest::AbstractEvalNode* parent)
{
    for (auto slot : m_inputSlots){
        slot->setParent(parent);
    }
    for (auto slot : m_outputSlots){
        slot->setParent(parent);
    }
}
