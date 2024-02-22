#pragma once

#include <utility>

#include <QDebug>

#include "Utils/debugutils.h"
#include "Global/typenamemacro.h"

//store pointer to heap data of any type
//provide type check by a simple Type registry

//T should have a copy constructor

namespace Nodest{

class Variant
{
public:

    template<typename T>
    Variant(){
        m_data = new T();
        m_typeid = TYPENAME<T>::getID();
    }

    template<typename T>
    Variant(const T& value){
        m_data = new T(value);
        m_typeid = TYPENAME<T>::getID();
    }

    template<typename T>
    Variant* clone(const Variant& other){
        return new Variant(other.get<T>());
    }

    //WARNING: we cannot have a templated destructor, so user must call this
    //function to manually free the pointer when Variant's lifetime ends

    //it's only used in the framework itself, DO NOT use Variant in user-defined node classes
    template<typename T>
    void destruct(){
        // qDebug() << "destruct Variant: " << QString(TYPENAME<T>::getName()) << " " << *(static_cast<T*>(m_data));
        delete static_cast<T*>(m_data);
        m_data = nullptr;
    }

    template<typename T>
    T& get(){
        return *(static_cast<T*>(m_data));
    }

    template<typename T>
    void set(const T& value){
        if (m_data){
            destruct<T>();
        }
        m_data = new T(value);
    }

    //set through a pointer, take the ownership of the pointer
    //no data copy, so safe when T contains pointers
    template<typename T>
    void setPointer(void* pointer){
        if (m_data){
            destruct<T>();
        }
        m_data = pointer;
    }

    template<typename T>
    T* getPointer(){
        return static_cast<T*>(m_data);
    }

    int getTypeId() const{
        return m_typeid;
    }



private:
    void* m_data;
    int m_typeid;
};

template <typename T>
Variant* createVariant(const T& value){
    return new Variant(value);
}

template <typename T>
Variant* createVariant(){
    return  new Variant(T());
}

}


