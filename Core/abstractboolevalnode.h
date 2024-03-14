#pragma once

#include "abstractevalnode.h"

namespace NF{

class AbstractBoolEvalNode : public AbstractEvalNode
{
public:
    AbstractBoolEvalNode() : AbstractEvalNode() {}

    virtual ~AbstractBoolEvalNode() {}

protected:

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
        bool rstTag = std::apply([&](auto&&... args) { bool rst = func(*(args)...); return rst; }, argsTuple);

    }

};

}
