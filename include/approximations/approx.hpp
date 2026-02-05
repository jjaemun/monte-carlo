#ifndef APPROX_HPP
#define APPROX_HPP

#include <array>
#include <cmath>
#include <type_traits>
#include <ranges>

#include "utitilities.hpp"


template <typename... Coeffs>
class Polynomial {

    static_assert(std::is_arithmetic_v<std::common_type_t<Coeffs...>>);

    private:
        static constexpr auto degree = pack_size<Coeffs...>;

    public:
        Polynomial(const Coeffs&... coeffs) : coeffs{ coeffs... } {}

        __attribute__((always_inline)) 
        template <typename T>
        constexpr T operator()(const T u) const noexcept {
            auto ret = (T)0.0; 
            for (const auto &coeff : coeffs | std::views::reverse) 
               ret = std::fma(ret, u, coeff);  
            
            return ret;
        }

    private:
        std::array<std::common_type_t<Coeffs...>, degree> coeffs;
};

template <typename... Coeffs>
class Polynomial {
    
    static_assert(std::is_arithmetic_v<std::common_type_t<Coeffs...>>);

    using type = std::common_type_t<Coeffs...>;

    private:
        static constexpr auto degree = pack_size<Coeffs...>;

    public:
        Polynomial(const Coeffs&... coeffs) : coeffs{ coeffs... } {}

        __attribute__((always_inline))constexpr type operator()(const type u) const noexcept {
            auto ret = (type)0.0; 
            for (const auto &coeff : coeffs | std::views::reverse) 
               ret = std::fma(ret, u, coeff);  
            
            return ret;
        }

    private:
        std::array<type, degree> coeffs;
}
