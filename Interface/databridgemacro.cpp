#include "databridgemacro.h"

QHash<int, NF::BridgeMetaData> &NF::bridgeIDToMetaData()
{
    static QHash<int, BridgeMetaData> map;
    return map;
}


QHash<NF::BridgeTypes, int> &NF::bridgeTypesToID()
{
    static QHash<BridgeTypes, int> map;
    return map;
}
