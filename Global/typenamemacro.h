#pragma once

//we have to get the exact name of a type, not something returned by
//typeid.name(), that is quite unstable

//Why don't use Qt's metatype system?
//to collaborate better with C++ templates, Qt's metatype system
//does not expose enough template functions to users

#include <QString>
#include <QHash>

static int typeValue = 0;
static QHash<int, QString> typenameMap;

#ifndef DECLARE_TYPE
#define DECLARE_TYPE(typeName) \
    template<> \
    struct TYPENAME<typeName>{ \
        static QString getName() { return QString(#typeName); } \
        static int getID() {return typeID;} \
        inline static int const typeID = typeValue++; \
    }; \

#endif


namespace Nodest{

template<typename T>
struct TYPENAME{
    static QString getName() { return QString("ErrorType"); }
    static int getID() { return -1; }
};



}




