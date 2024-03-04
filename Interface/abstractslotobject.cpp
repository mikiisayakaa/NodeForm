#include "abstractslotobject.h"
#include "Extension/abstractextension.h"

NF::AbstractSlotObject::AbstractSlotObject(NF::AbstractSlot *slot, QObject *parent)
    :QObject(parent), m_slot(slot)
{

}

void NF::AbstractSlotObject::addExtension(NF::AbstractExtension *extension)
{

    for (size_t i = 0; i < m_extensions.size(); i++){
        if (m_extensions[i]->getExtensionType() == extension->getExtensionType()){
            return;
        }
    }


    if (extension->addExtension(m_items[0])){
        m_extensions.push_back(extension);
    }
    else{
        delete extension;
    }


}
