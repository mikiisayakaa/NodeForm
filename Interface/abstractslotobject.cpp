#include "abstractslotobject.h"

Nodest::AbstractSlotObject::AbstractSlotObject(Nodest::AbstractSlot *slot, QObject *parent)
    :QObject(parent), m_slot(slot)
{

}
