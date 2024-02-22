#pragma once

#include <vector>

#include "Wrapper/abstractslotsetter.h"
#include "Wrapper/abstractslotgetter.h"
#include "Wrapper/slotsettermacro.h"
#include "Wrapper/slotgettermacro.h"
#include "Core/inputslot.h"
#include "tupleutils.h"

#include <QQuickItem>

namespace Nodest{


//create setters for a slot vector
template <typename ArgumentTuple, int Index>
struct RecursiveSetterCreator {
    static void instantiate(std::vector<InputSlot*>& slotvec) {
        using ElementType = typename std::tuple_element_t<Index, ArgumentTuple>;

        //if no proper SlotSetter is defined, set setter to nullptr
        if (!IsSameType<typename SetterTypeMapper<ElementType>::Type, int>::value){
            AbstractSlotSetter* setter = SetterTypeMapper<ElementType>::createInstance();
            setter->setSlot(slotvec[Index]);
            slotvec[Index]->setSetter(setter);
        }
        else{
            slotvec[Index]->setSetter(nullptr);
            slotvec[Index]->getParent()->addDepend(1);
        }

        RecursiveSetterCreator<ArgumentTuple, Index - 1>::instantiate(slotvec);
    }
};

//end of recrusion
template <typename ArgumentTuple>
struct RecursiveSetterCreator<ArgumentTuple, -1> {
    static void instantiate(std::vector<InputSlot*>&) {}
};

//create getters for a slot vector
template <typename ArgumentTuple, int Index>
struct RecursiveGetterCreator {
    static void instantiate(std::vector<OutputSlot*>& slotvec) {
        using ElementType = typename std::tuple_element_t<Index, ArgumentTuple>;

        //if no proper SlotSetter is defined, set setter to nullptr
        if (!IsSameType<typename GetterTypeMapper<ElementType>::Type, int>::value){
            AbstractSlotGetter* getter = GetterTypeMapper<ElementType>::createInstance();
            getter->setSlot(slotvec[Index]);
            slotvec[Index]->setGetter(getter);
        }
        else{
            slotvec[Index]->setGetter(nullptr);
        }

        RecursiveGetterCreator<ArgumentTuple, Index - 1>::instantiate(slotvec);
    }
};

//end of recrusion
template <typename ArgumentTuple>
struct RecursiveGetterCreator<ArgumentTuple, -1> {
    static void instantiate(std::vector<OutputSlot*>&) {}
};

//bind the setters to QML widgets
template <typename ArgumentTuple, int Index>
struct RecursiveSetterBinder{
    static void bindSetter(std::vector<InputSlot*>& slotvec,
                           QQuickItem* item, int index){
        using ElementType = typename std::tuple_element_t<Index, ArgumentTuple>;
        using SetterType = typename SetterTypeMapper<ElementType>::Type;
        using QMLType = typename SetterTypeMapper<ElementType>::QMLType;

        if(Index == index && slotvec[Index]->getSetter() != nullptr){
            //trick here: we cannot use SIGNAL() and SLOT() macro here
            //SIGNAL() and SLOT() are simple string macros, so they simply
            //change ElementType into "ElementType", do not take template into account
            QObject::connect(item,
                             (QString("2dataSignal(") + TYPENAME<QMLType>::getName() + ")").toStdString().c_str(),
                             slotvec[Index]->getSetter(),
                             (QString("1receiveValue(") + TYPENAME<QMLType>::getName() + ")").toStdString().c_str());
        }

        RecursiveSetterBinder<ArgumentTuple, Index - 1>::bindSetter(slotvec, item, index);
    }
};

//end of recursion
template <typename ArgumentTuple>
struct RecursiveSetterBinder<ArgumentTuple, -1>{
    static void bindSetter(std::vector<InputSlot*>&, QQuickItem*, int) {}
};

}
