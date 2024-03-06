#include "basicnodemacro.h"

namespace NF {

QHash<int, NodeMetaData> &nodeIDToMetaData()
{
   static QHash<int, NodeMetaData> map;
   return map;
}

QHash<QString, int> &nodeNameToID()
{
    static QHash<QString, int> map;
    return map;
}

}
