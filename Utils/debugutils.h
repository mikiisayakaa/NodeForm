#pragma once

#include <QString>
#include <string>

namespace NodestDebug{

//not registered metatype error, user should be responsible for registration
std::string metaTypeUnRegistered(const char* typeName);

//connecting multiple output slots to an input slot
std::string tooManyInputConnections();


std::string wrongDataType(const char* targetName, const char* realName);

}
