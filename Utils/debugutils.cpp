#include "debugutils.h"

namespace NodestDebug{

std::string metaTypeUnRegistered(const char* typeName){
    QString errMessage1("Type Error: User type [");
    QString errMessage2("] is not registered in QMetaType system!\n");

    return (errMessage1 + QString(typeName) + errMessage2).toStdString();
}

std::string tooManyInputConnections(){
    QString errMessage("Connection Error: connecting more than 1 slot to "
                       "an input slot!\n");
    return errMessage.toStdString();
}

std::string wrongDataType(const char *targetName, const char *realName)
{
    QString errMessage1("Target type [");
    QString errMessage2("] do not fit real type [");
    QString errMessage3("] !");

    return (errMessage1 + QString(targetName) + errMessage2 + QString(realName)
            + errMessage3).toStdString();
}

}
