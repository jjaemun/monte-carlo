#ifndef NORMINV_HPP 
#define NORMINV_HPP 

#include <cmath>
#include <limits>
#include <numbers>
#include <ranges>


#include "approximation/approx.hpp"
#include "types.hpp"


[[nodiscard]]
#if defined(__GNUC__) || defined(__clang__)
__attribute__((hot, always_inline))
#endif
constexpr f64 __norminv_wichura(const f64 u) noexcept {

    /* ALGO. AS241 APPL. STATIST. (Wichura, 1988) 
          VOL. 37, NO 3. */

    const auto split1 = (f64)0.425e0; 
    const auto split2 = (f64)5.0e0; 

    const auto const1 = (f64)0.180625e0; 
    const auto const2 = (f64)1.6e0;


    // coeffs. for u close to 1/2.
    static constexpr Polynomial a(
        (f64)3.3871328727963666080e0, 
        (f64)1.3314166789178437745e2,
        (f64)1.9715909503065514427e3, 
        (f64)1.3731693765509461125e4,
        (f64)4.5921953931549871457e4, 
        (f64)6.7265770927008700853e4,
        (f64)3.3430575583588128105e4, 
        (f64)2.5090809287301226727e3
    );

    static constexpr Polynomial b(
        (f64)1.0                    , 
        (f64)4.2313330701600911252e1,
        (f64)6.8718700749205790830e2, 
        (f64)5.3941960214247511077e3,
        (f64)2.1213794301586595867e4, 
        (f64)3.9307895800092710610e4,
        (f64)2.8729085735721942674e4, 
        (f64)5.2264952788528545610e3   
    );
    
    // coeffs. for u neither close to 1/2 nor 0 or 1.
    static constexpr Polynomial c(
        (f64)1.42343711074968357734e0, 
        (f64)4.63033784615654529590e0,
        (f64)5.76949722146069140550e0, 
        (f64)3.64784832476320460504e0,
        (f64)1.27045825245236838258e0, 
        (f64)2.41780725177450611770e-1,
        (f64)2.27238449892691845833e-2, 
        (f64)7.74545014278341407640e-4
    );

    static constexpr Polynomial d(
        (f64)1.0                     , 
        (f64)2.05319162663775882187e0, 
        (f64)1.67638483018380384940e0, 
        (f64)6.89767334985100004550e-1,
        (f64)1.48103976427480074590e-1, 
        (f64)1.51986665636164571966e-2,
        (f64)5.47593808499534494600e-4, 
        (f64)1.05075007164441684324e-9
    );

   
    // coeffs. for u very near 0 or 1
    static constexpr Polynomial e(
        (f64)6.65790464350110377720e0, 
        (f64)5.46378491116411436990e0,
        (f64)1.78482653991729133580e0, 
        (f64)2.96560571828504891230e-1,
        (f64)2.65321895265761230930e-2, 
        (f64)1.24266094738807843860e-3,
        (f64)2.71155556874348757815e-5, 
        (f64)2.01033439929228813265e-7
    );

    static constexpr Polynomial f(
        (f64)1.0                     , 
        (f64)5.99832206555887937690e-1,
        (f64)1.36929880922735805310e-1, 
        (f64)1.48753612908506148525e-2,
        (f64)7.86869131145613259100e-4, 
        (f64)1.84631831751005468180e-5,
        (f64)1.42151175831644588870e-7, 
        (f64)2.04426310338993978564e-15
    );

    if (u <= (f64)0.0) 
        return -std::numeric_limits<f64>::infinity();

    if (u >= (f64)1.0)
        return std::numeric_limits<f64>::infinity();

    const auto Q = u - (f64)(1.0 / 2.0);
    if (std::abs(Q) <= split1) {
        const f64 R = const1 - Q * Q;
        return Q * a(R) / b(R);
    }

    else {
        f64 R{};
        if (Q < 0.0)
            R = std::sqrt(-std::log(u));
        else 
            R = std::sqrt(-std::log((f64)1.0 - u));

        f64 ret{};
        if (R < split2) {
            R -= const2;
            ret = c(R) / d(R);
        }

        else {
            R -= split2;
            ret = e(R) / f(R);
        }
            
        if (Q < (f64)0.0)
            return -ret;

        return ret;
    }
}

#endif
