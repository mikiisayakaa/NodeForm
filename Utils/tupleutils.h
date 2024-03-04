#pragma once

#include <tuple>

namespace NF{
//utils for parsing a void* function pointer

//count the const parameter of a tuple
template <typename T>
struct CountConst;

template <>
struct CountConst<std::tuple<>> {
    static constexpr std::size_t value = 0;
};

template <typename T, typename... Ts>
struct CountConst<std::tuple<T, Ts...>> {
    static constexpr std::size_t value =
        std::is_const<T>::value + CountConst<std::tuple<Ts...>>::value;
};

//we can get a tuple type containing all parameters if we use the function pointer as
//template parameter
template <typename... Args>
struct FunctionTraits;

template <typename... Args>
struct FunctionTraits<void (*)(Args...)> {
    //remove all const and reference keywords
    using argument_types = std::tuple<std::remove_const_t<
        std::remove_reference_t<Args>>...>;

    static constexpr size_t K = CountConst<std::tuple<std::remove_reference_t<Args>...>>::value;

    using functionType = void (*)(Args...);
};

template <typename... Args>
struct FunctionTraits<bool (*)(Args...)> {
    using argument_types = std::tuple<std::remove_const_t<
        std::remove_reference_t<Args>>...>;

    static constexpr size_t K = CountConst<std::tuple<std::remove_reference_t<Args>...>>::value;

    using functionType = bool (*)(Args...);
};

//assistant function to split the first K elements to create a new tuple
//needs a tuple instance and will return another tuple instance
template <size_t K, typename Tuple, size_t... Index>
auto take_front_impl(const Tuple& t, std::index_sequence<Index...>) {
    return std::make_tuple(std::get<Index>(t)...);
}

template <size_t K, typename... Types>
auto take_front(const std::tuple<Types...>& t) {
    return take_front_impl<K>(t, std::make_index_sequence<K>());
}

//assistant function to drop the first K elements and create a new tuple type for other elements
//needs a tuple instance and will return another tuple instance
template <size_t K, typename Tuple, size_t... Index>
auto drop_front_impl(const Tuple& t, std::index_sequence<Index...>) {
    return std::make_tuple(std::get<K + Index>(t)...);
}

template <size_t K, typename... Types>
auto drop_front(const std::tuple<Types...>& t) {
    return drop_front_impl<K>(t, std::make_index_sequence<sizeof...(Types) - K>());
}

//better tuple splitter for the front k types in the tuple, do not involve any instances
template <typename Tuple, std::size_t K, typename = std::make_index_sequence<K>>
struct TupleSplitterFrontK_impl;

template <typename... Types, std::size_t... Indices>
struct TupleSplitterFrontK_impl<std::tuple<Types...>, 0, std::index_sequence<Indices...>> {
    using type = std::tuple<>;
};

template <typename... Types, std::size_t K, std::size_t... Indices>
struct TupleSplitterFrontK_impl<std::tuple<Types...>, K, std::index_sequence<Indices...>> {
    using type = std::tuple<std::tuple_element_t<Indices, std::tuple<Types...>>...>;
};

template <typename Tuple, std::size_t K>
using TupleSplitterFrontK = typename TupleSplitterFrontK_impl<Tuple, K>::type;

//better tuple dropper for the front k types in the tuple, do not involve any instances
template <typename Tuple, std::size_t K,
          typename = std::make_index_sequence<std::tuple_size_v<Tuple> - K>>
struct TupleDropperFrontK_impl;

template <typename... Types, std::size_t... Indices>
struct TupleDropperFrontK_impl<std::tuple<Types...>, 0, std::index_sequence<Indices...>> {
    using type = std::tuple<Types...>;
};

template <typename... Types, std::size_t K, std::size_t... Indices>
struct TupleDropperFrontK_impl<std::tuple<Types...>, K, std::index_sequence<Indices...>> {
    using type = std::tuple<std::tuple_element_t<K + Indices, std::tuple<Types...>>...>;
};

template <typename Tuple, std::size_t K>
using TupleDropperFrontK = typename TupleDropperFrontK_impl<Tuple, K>::type;

template <typename FunctionType>
struct TupleTypes{
    using TraitsType = FunctionTraits<FunctionType>;
    using ArgumentTypes = typename TraitsType::argument_types;

    using InputArgumentTypes = TupleSplitterFrontK<ArgumentTypes, TraitsType::K>;
    using OutputArgumentTypes = TupleDropperFrontK<ArgumentTypes, TraitsType::K>;
};

//compile time type compare
template <typename T, typename U>
struct IsSameType{
    static constexpr bool value = std::is_same_v<T, U>;
};

}
