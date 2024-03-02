#include "slotobject.h"
#include "Global/globalitems.h"
#include "Global/globalqmlfiles.h"
#include "Global/globaluiparams.h"
#include "connectionobject.h"
#include "tempconnectionobject.h"
#include "Utils/qmlcreationutils.h"
#include "abstractgraphobject.h"
#include "Extension/extensionfactory.h"

Nodest::SlotObject::SlotObject(Nodest::AbstractSlot *slot, QObject *parent)
    :AbstractSlotObject (slot, parent), m_testConnection(nullptr), m_tempConnection(nullptr)
{

}


void Nodest::SlotObject::addExtensions()
{
    std::vector<ExtensionType> extensionList{
        ExtensionType::DragAddConnection
    };

    for (auto& type : extensionList){
        AbstractExtension* extension = ExtensionFactory::createExtension(type, this);
        addExtension(extension);
    }
}


