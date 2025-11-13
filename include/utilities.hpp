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


template <typename T>
constexpr auto count_from_bytes(size_t bytes) -> size_t {
    return static_cast<size_t>(bytes / sizeof(T));
}

template <typename... Ts>
constexpr auto pack_size = sizeof...(Ts);


#endif
