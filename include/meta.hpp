#ifndef META_HPP
#define META_HPP


#include <tuple>

#include "utility.hpp"


template <typename Container, std::size_t... Is>
constexpr auto meta_reverse(Container&& c, std::index_sequence<Is...>) {
    constexpr std::size_t s = std::tuple_size_v<std::remove_reference_t<Container>>;
    return std::make_tuple(std::get<s - 1 -Is>(std::forward<Container>(c))...);
}

template <typename Container>
constexpr auto reverse(Container&& c) {
    constexpr std::size_t s = std::tuple_size_v<std::remove_reference_t<Container>>;
    return meta_reverse(std::forward<Container>(c), std::make_index_sequence<s>{});
}
    


#endif
