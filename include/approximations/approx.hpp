#ifndef APPROX_HPP
#define APPROX_HPP

#include <array>
#include <cmath>
#include <type_traits>
#include <ranges>

#include "utitilities.hpp"


template <typename... Coeffs>
class Polynomial {

    template <typename... Types>
    using type = std::common_type_t<Types...>;
    
    static_assert(std::is_arithmetic_v<type<Coeffs...>>);

    public:
        Polynomial(const Coeffs&... coeffs) : coeffs{ coeffs... } {}
        std::array<type<Coeffs...>, pack_size<Coeffs...>> coeffs;
};


#endif
