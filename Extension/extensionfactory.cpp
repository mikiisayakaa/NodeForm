#include "extensionfactory.h"

#include "extensiontypes.h"

#include "Extension/Graph/graphconnectionselectionextension.h"
#include "Extension/Graph/graphnodeselectionextension.h"
#include "Extension/Node/nodeselectionextension.h"
#include "Extension/Connection/connectionselectionextension.h"

Nodest::AbstractExtension *Nodest::ExtensionFactory::createExtension(Nodest::ExtensionType type, QObject *parent)
{
    switch(type){

    case ExtensionType::GraphConnectionSelection:
        return new GraphConnectionSelectionExtension(parent);

    case ExtensionType::GraphNodeSelection:
        return new GraphNodeSelectionExtension(parent);

    case ExtensionType::NodeSelection:
        return new NodeSelectionExtension(parent);

    case ExtensionType::ConnectionSelection:
        return new ConnectionSelectionExtension(parent);

    default:
        break;
    }

    return nullptr;
}
