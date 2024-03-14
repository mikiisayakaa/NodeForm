#pragma once

#include <iostream>
#include <algorithm>
#include <functional>

#include "abstractnode.h"
#include "abstractslot.h"
#include "Utils/tupleutils.h"
#include "Utils/slottupleutils.h"
#include "Interface/abstractnodeobject.h"

namespace NF{

class AbstractEvalNode : public AbstractNode
{

public:
    explicit AbstractEvalNode() : AbstractNode() {}

    //virtual clone for runtime clone of children using AbstractNode pointer
    virtual AbstractEvalNode* clone() const = 0;

    virtual ~AbstractEvalNode() {}

    virtual void eval() = 0;

    virtual void setValue(int slotIndex, void* ptr) = 0;

protected:
    //we can't use a template BasicNode class, since it conflicts with Qt metaObject system

    //raise the InputArgsTypes to outer template parameter, we need it to define init values
    template<typename FunctionType>
    void constructImpl(){
        using TP = TupleTypes<FunctionType>;
        using OutArgsTypes = typename TP::OutputArgumentTypes;
        using InArgsTypes = typename TP::InputArgumentTypes;

        RecursiveInstantiatorS<InArgsTypes, InputSlot, std::tuple_size_v<InArgsTypes> - 1>::instantiate(InArgsTypes{}, m_inputSlots);
        RecursiveInstantiatorS<OutArgsTypes, OutputSlot, std::tuple_size_v<OutArgsTypes> - 1>::instantiate(OutArgsTypes{}, m_outputSlots);

        std::reverse(m_inputSlots.begin(), m_inputSlots.end());
        std::reverse(m_outputSlots.begin(), m_outputSlots.end());

        for (size_t i = 0; i < getNInput(); i++){
            m_inputSlots[i]->setIndex(i);
        }
        for (size_t i = 0; i < getNOutput(); i++){
            m_outputSlots[i]->setIndex(i);
        }

        setSlotParent(this);
    }

    //calculate the user provided function
    template<typename FunctionType>
    void evalImpl(FunctionType func){
        using TP = TupleTypes<FunctionType>;
        using InArgsTypes = typename TP::InputArgumentTypes;
        using OutArgsTypes = typename TP::OutputArgumentTypes;

        //get input args pointers tuple
        auto inputTuple = RecursiveSlotDumperP<InArgsTypes, InputSlot,
                std::tuple_size_v<InArgsTypes> - 1>::dumpArgs(m_inputSlots);

        //get output args pointers tuple
        auto outputTuple = RecursiveSlotDumperP<OutArgsTypes, OutputSlot,
                std::tuple_size_v<OutArgsTypes> - 1>::dumpArgs(m_outputSlots);

        auto argsTuple = std::tuple_cat(inputTuple, outputTuple);

        //dereference pointers
        std::apply([&](auto&&... args) { func(*(args)...); }, argsTuple);

    }

    template<typename FunctionType>
    void setValueImpl(int slotIndex, void*& ptr){
        using TP = TupleTypes<FunctionType>;
        using InArgsTypes = typename TP::InputArgumentTypes;

        RecursiveSlotSetter<InArgsTypes, InputSlot,
                std::tuple_size_v<InArgsTypes> - 1>::setSlot(m_inputSlots, slotIndex, ptr);
    }


    //we need the function pointer type to determine the
    //template for Slots' destructors
    template<typename FunctionType>
    void destruct(){
        using TP = TupleTypes<FunctionType>;
        using InArgsTypes = typename TP::InputArgumentTypes;
        using OutArgsTypes = typename TP::OutputArgumentTypes;

        RecursiveSlotDestructor<InArgsTypes, InputSlot,
                std::tuple_size_v<InArgsTypes> - 1>::destructSlots(m_inputSlots);
        RecursiveSlotDestructor<OutArgsTypes, OutputSlot,
                std::tuple_size_v<OutArgsTypes> - 1>::destructSlots(m_outputSlots);

    }

    void setSlotParent(AbstractEvalNode* parent);

protected:

};



}

