#pragma once

#include <QString>

#include "debugutils.h"
#include "Global/typenamemacro.h"

/* Store pointer to data of any type.
 * Provide type check by a simple Type registry.
*/

namespace Nodest{

class Variant
{
public:
    /* WARNING: we cannot have a templated destructor, so we must call this
     * function to manually free the pointer when the Variant's lifetime ends.
     *
     * This is only used in the framework itself, DO NOT use Variant in user-defined node classes.
    */
    template<typename T>
    void destruct(){
        ND_ASSERT(m_typeid == TYPENAME<T>::getID(), QString("Destructing wrong type [") + TYPENAME<T>::getName() +
                  "]'s value, correct type is [" + getTypeName() + "]");
        delete static_cast<T*>(m_data);
        m_data = nullptr;
    }

    template<typename T>
    T& get(){
        ND_ASSERT(m_typeid == TYPENAME<T>::getID(), QString("Getting wrong type [") + TYPENAME<T>::getName() +
                  "]'s value from Variant with type [" + getTypeName() + "]");
        return *(static_cast<T*>(m_data));
    }

    template<typename T>
    void set(const T& value){
        ND_ASSERT(m_typeid == TYPENAME<T>::getID(), QString("Setting wrong type [") + TYPENAME<T>::getName() +
                  "]'s value to Variant with type [" + getTypeName() + "]");

        if (m_data){
            destruct<T>();
        }
        m_data = new T(value);
    }

    template<typename T>
    T* getPointer(){
        ND_ASSERT(m_typeid == TYPENAME<T>::getID(), QString("Getting wrong type [") + TYPENAME<T>::getName() +
                  "]'s pointer from Variant with type [" + getTypeName() + "]");
        return static_cast<T*>(m_data);
    }

    /* Set through a pointer, take the ownership of the pointer.
     * No data copy, so safe when T contains pointers.
    */
    template<typename T>
    void setPointer(void* pointer){
        ND_ASSERT(m_typeid == TYPENAME<T>::getID(), QString("Filling wrong type [") + TYPENAME<T>::getName() +
                  "]'s pointer to Variant with type [" + getTypeName() + "]");
        if (m_data){
            destruct<T>();
        }
        m_data = pointer;
    }

    int getTypeId() const {return m_typeid;}

    QString getTypeName() const {return typenameMap[m_typeid];}

    template <typename T>
    static Variant* createVariant(const T& value){
        return new Variant(value);
    }

    // This function assumes the user has provided a correct default constructor
    template <typename T>
    static Variant* createVariant(){
        return new Variant(T());
    }

private:
    Variant() {}

    // Variant assumes the user has provided a correct copy constructor
    template<typename T>
    Variant(const T& value){
        m_data = new T(value);
        m_typeid = TYPENAME<T>::getID();

        // runtime creation of typeid->typename map
        if (typenameMap.find(m_typeid) == typenameMap.end()){
            typenameMap.insert(m_typeid, TYPENAME<T>::getName());
        }

        ND_ASSERT(m_typeid != -1, QString("Type: [") + typeid(T).name() +
                  "] has not been registered, use DECLARE_TYPE() first");

    }

private:
    void* m_data;
    int m_typeid;
};

}


