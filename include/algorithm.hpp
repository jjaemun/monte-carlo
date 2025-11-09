#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP


#include <type_traits>
#include <tuple>

#include "utilities.hpp"

namespace detail {
    template <typename Tuple, std::size_t... Is>
    constexpr auto reverse(Tuple&& tp, std::index_sequence<Is...>) {
        constexpr std::size_t s = std::tuple_size_v<std::remove_reference_t<Tuple>>;
        return std::make_tuple(std::get<s - 1 -Is>(std::forward<Tuple>(tp))...);
    }
}

template <typename Tuple>
constexpr auto reverse(Tuple&& tp) {
    constexpr std::size_t s = std::tuple_size_v<std::remove_reference_t<Tuple>>;
    return detail::reverse(std::forward<Tuple>(tp), std::make_index_sequence<s>{});
}
    

#endif
