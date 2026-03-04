#ifndef APPROX_HPP
#define APPROX_HPP


#include <array>
#include <cmath>
#include <type_traits>
#include <ranges>

#include "utilities.hpp"


template <typename... Coeffs>
class Polynomial {

    /**
     * Constructs a polynomial of arbitrary degree (pack_size<Coeffs...> - 1)
     * with Horner evaluation. Uses a variadic pack of coefficients to resolve
     * implicitly array size at compile time.
    */

    template <typename... Types>
    using type = std::common_type_t<Types...>;
    
    static_assert(std::is_arithmetic_v<type<Coeffs...>>);

    public:
        constexpr Polynomial(Coeffs&&... coeffs) noexcept : 
            coeffs{ std::forward<Coeffs>(coeffs)... } {}

        [[nodiscard]]
        #if defined(__GNUC__) || defined(__clang__)

            /**
             * If available, forcing inline improves performance, but is
             * generally superfluous.
             */

        __attribute__((always_inline))
        #endif
        constexpr type<Coeffs...> operator()(const type<Coeffs...> u) const noexcept {
     
            /**
             * std::fma is chosen to reduce rounding errors. The performance hit
             * of stl machinery is considerable in this case. std::views::reverse
             * is opaque and prevents aggresive loop unrolling.
             */

           auto ret = (type<Coeffs...>)0.0; 
            for (const auto &coeff : coeffs | std::views::reverse) 
               ret = std::fma(ret, u, coeff);  
            
            return ret;
        }

    private:
        std::array<type<Coeffs...>, pack_size<Coeffs...>> coeffs;
};


template <typename... Coeffs>
Polynomial(Coeffs...) -> Polynomial<Coeffs...>;

#endif
