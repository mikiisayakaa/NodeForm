#include "connectionobject.h"
#include "abstractgraphobject.h"
#include "basicgraphobject.h"

#include "Extension/extensionfactory.h"


void NF::ConnectionObject::addExtensions()
{
    std::vector<ExtensionType> extensionList{
        ExtensionType::ConnectionSelection
    };

    for (auto& type : extensionList){
        AbstractExtension* ext = ExtensionFactory::createExtension(type, this);
        addExtension(ext);
    }
}

