#include "connectionobject.h"
#include "abstractgraphobject.h"
#include "basicgraphobject.h"

#include "Extension/extensionfactory.h"


void Nodest::ConnectionObject::addExtensions()
{
    AbstractExtension* ext1 = ExtensionFactory::createExtension(ExtensionType::ConnectionSelection, this);
    addExtension(ext1);
}

