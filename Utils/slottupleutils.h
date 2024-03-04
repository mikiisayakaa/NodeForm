#pragma once

#include <tuple>
#include <vector>

#include "Core/inputslot.h"

namespace NF{

//recursively parse a std::tuple to create slots (reverse sequence)
template <typename ArgumentTuple, typename SlotType, int Index>
struct RecursiveInstantiatorS {
    static void instantiate(const ArgumentTuple& args, std::vector<SlotType*>& slotvec) {
        using ElementType = typename std::tuple_element_t<Index, ArgumentTuple>;

        slotvec.push_back(SlotType::template createSlot<ElementType>(std::get<Index>(args)));

        RecursiveInstantiatorS<ArgumentTuple, SlotType, Index - 1>::instantiate(args, slotvec);
    }
};

//end of recursion
template <typename ArgumentTuple, typename SlotType>
struct RecursiveInstantiatorS<ArgumentTuple, SlotType, -1> {
    static void instantiate(const ArgumentTuple&, std::vector<SlotType*>&) {}
};

// recursively fill a pointer std::tuple from slots
template <typename ArgumentTuple, typename SlotType, int Index>
struct RecursiveSlotDumperP {
    static auto dumpArgs(const std::vector<SlotType*>& slotvec) {
        using ElementType = typename std::tuple_element_t<Index, ArgumentTuple>;

        ElementType* value;
        value = slotvec[Index]->template getPointer<ElementType>();

        auto restTuple = RecursiveSlotDumperP<ArgumentTuple, SlotType, Index - 1>::dumpArgs(slotvec);

        return std::tuple_cat(restTuple, std::make_tuple(value));
    }
};

// end of recursion
template <typename ArgumentTuple, typename SlotType>
struct RecursiveSlotDumperP<ArgumentTuple, SlotType, -1>{
    static auto dumpArgs(const std::vector<SlotType*>&){
        return std::tuple<>{};
    }
};

//recursively fill a value std::tuple from slots
template <typename ArgumentTuple, typename SlotType, int Index>
struct RecursiveSlotDumper {
    static auto dumpArgs(const std::vector<SlotType*>& slotvec) {
        using ElementType = typename std::tuple_element_t<Index, ArgumentTuple>;

        ElementType value;
        value = slotvec[Index]->template get<ElementType>();

        auto restTuple = RecursiveSlotDumper<ArgumentTuple, SlotType, Index - 1>::dumpArgs(slotvec);

        return std::tuple_cat(restTuple, std::make_tuple(value));
    }
};

// end of recursion
template <typename ArgumentTuple, typename SlotType>
struct RecursiveSlotDumper<ArgumentTuple, SlotType, -1>{
    static auto dumpArgs(const std::vector<SlotType*>&){
        return std::tuple<>{};
    }
};

//recursively fill slots from a std::tuple
template <typename ArgumentTuple, typename SlotType, int Index>
struct RecursiveSlotLoader {
    static void loadArgs(const ArgumentTuple& args, std::vector<SlotType*>& slotvec) {
        using ElementType = typename std::tuple_element_t<Index, ArgumentTuple>;
        slotvec[Index]->template set<ElementType>(std::get<Index>(args));

        RecursiveSlotLoader<ArgumentTuple, SlotType, Index - 1>::loadArgs(args, slotvec);
    }
};

//end of recursion
template <typename ArgumentTuple, typename SlotType>
struct RecursiveSlotLoader<ArgumentTuple, SlotType, -1> {
    static void loadArgs(const ArgumentTuple&, std::vector<SlotType*>&) {}
};

//recursively destruct all slot pointers
template <typename ArgumentTuple, typename SlotType, int Index>
struct RecursiveSlotDestructor {
    static void destructSlots(std::vector<SlotType*>& slotvec){
        using ElementType = typename std::tuple_element_t<Index, ArgumentTuple>;
        slotvec[Index]->template destruct<ElementType>();

        RecursiveSlotDestructor<ArgumentTuple, SlotType, Index - 1>::destructSlots(slotvec);
    }
};

//end of recursion
template <typename ArgumentTuple, typename SlotType>
struct RecursiveSlotDestructor<ArgumentTuple, SlotType, -1> {
    static void destructSlots(std::vector<SlotType*>&){}
};

//recursively print all slots's values
template <typename ArgumentTuple, typename SlotType, int Index>
struct RecursiveSlotPrinter{
    static void printSlots(const std::vector<SlotType*>& slotvec){
        using ElementType = typename std::tuple_element_t<Index, ArgumentTuple>;
        slotvec[Index]->template verbose<ElementType>();

        RecursiveSlotPrinter<ArgumentTuple, SlotType, Index - 1>::printSlots(slotvec);
    }
};

//end of recursion
template <typename ArgumentTuple, typename SlotType>
struct RecursiveSlotPrinter<ArgumentTuple, SlotType, -1>{
    static void printSlots(const std::vector<SlotType*>&){}
};

//recursively deep copy of a slot vector
template <typename ArgumentTuple, int Index>
struct RecursiveSlotCopier{
    static void copySlots(const std::vector<InputSlot*>& fromSlots, std::vector<InputSlot*>& toSlots){
        using ElementType = typename std::tuple_element_t<Index, ArgumentTuple>;

        RecursiveSlotCopier<ArgumentTuple, Index - 1>::copySlots(fromSlots, toSlots);
    }
};

//end of recursion
template <typename ArgumentTuple>
struct RecursiveSlotCopier<ArgumentTuple, -1>{
    static void copySlots(const std::vector<InputSlot*>&, std::vector<InputSlot*>&){}
};

//traverse slots and set value for the target indexed slot
template <typename ArgumentTuple, typename SlotType, int Index>
struct RecursiveSlotSetter{
    static void setSlot(const std::vector<SlotType*>& slotvec, int slotIndex, void*& ptr){
        if (slotIndex == Index){
            using ElementType = typename std::tuple_element_t<Index, ArgumentTuple>;

            slotvec[slotIndex]->template setPointer<ElementType>(ptr);

            return;
        }
        else{
            RecursiveSlotSetter<ArgumentTuple, SlotType, Index - 1>::setSlot(slotvec, slotIndex, ptr);
        }
    }
};

//end of recursion
template<typename ArgumentType, typename SlotType>
struct RecursiveSlotSetter<ArgumentType, SlotType, -1>{
    static void setSlot(const std::vector<SlotType*>&, int, void*&) {}
};

}
