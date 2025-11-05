#ifndef UTILITIES_HPP 
#define UTILITIES_HPP


#include <utility>


template <typename To, typename From>
constexpr auto down_cast(From &&from) -> To&& {
    return static_cast<To&&>(std::forward<From>(from));
}


template <typename To, typename From>
constexpr auto down_cast(From &from) -> To& {
    return static_cast<To&>(from);
}


template <typename To, typename From>
constexpr auto down_cast(const From &from) -> const To& {
    return static_cast<const To&>(from);
}


#endif
