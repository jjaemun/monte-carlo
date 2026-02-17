#ifndef APPROX_HPP
#define APPROX_HPP


#include <array>
#include <cmath>
#include <type_traits>
#include <ranges>

#include "utitilities.hpp"


template <typename... Coeffs>
class Polynomial {

    /**
     * Constructs a polynomial of arbitrary degree using
     * Horner evaluation. 
    */

    template <typename... Types>
    using type = std::common_type_t<Types...>;
    
    static_assert(std::is_arithmetic_v<type<Coeffs...>>);

    public:
        Polynomial(const Coeffs&... coeffs) : coeffs{ coeffs... } {}

        #if defined(__GNUC__) || defined(__clang__)
        __attribute__((always_inline))
        #endif
        constexpr type<Coeffs...> operator()(const type<Coeffs...> u) const noexcept {
     
            /**
            * If available, forcing inline improves performance, but is 
            * generally superfluous. It neither seems to propagate beyond 
            * the function scope in a way that interferes with general 
            * optimizations at compile-time.
            */

           auto ret = (type<Coeffs...>)0.0; 
            for (const auto &coeff : coeffs | std::views::reverse) 
               ret = std::fma(ret, u, coeff);  
            
            return ret;
        }

    private:
        std::array<type<Coeffs...> pack_size<Coeffs...>> coeffs;
};


#endif
