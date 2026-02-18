#ifndef RLOGONE_HPP 
#define RLOGONE_HPP 


#include <cmath>

#include "approximation/approx.hpp"
#include "types.hpp"


[[nodiscard]]
#if defined(__GNUC__) || defined(__clang__)
__attribute__((hot, always_inline))
#endif
constexpr f64 __rlog_one(const f64 u) noexcept {

    /**
          ALGO. 708, TOMS (Didonato & Morris, 1992)
              VOL. 18, NO. 3.

        ~ Significant Digit Computations of the Incomplete 
            Beta Function Ratios ~
        
     * Evaluates the function 

                  ƒ(u) =  u - log(1 + u).
     
     * Clearly, issues arise for small u, where 
        
           ƒ(u) = u - log(1 + u) 

                                u^(i)    
                = ∑   (-1)^(i) ------- , 
                i = 2             i
                                       
     * since 
            
                            u->0
                log(1 + u)  ≈≈≈≈    u,

     * causing catastrofic cancellation. 

     * Now, in order that stability be preserved over
     * the problematic interval we use a minimax rational
     * approximation. This interval is an observed open 
     * set where smallness of u is known to cause IEEE fp 
     * precision errors. 
     
     * Although the rational approximation is global on 
     * the interval, it is split into regions. Each then 
     * uses corrections, in the form of a small linear
     * bias to flatten relative errors. A region-local
     * affine coordinate is used to condition them.
     
     * It is important to note that a (symmetry-inducing)
     * Mobius transform is used to keep the argument finite
     * as u -> -1,
     
                    mobius = u / (u + 2).

     * It therefore symmetrizes the error, bounds the 
     * variable tighter, and improves conditioning. 
     * However, it induces near odd behavior and hence,
     
                    even = mobius * mobius

     * follows.

     * Beyond it, direct evaluation is stable.
     
     * There is no actual mention of this function in the
     * listed source. It is provided as supplementary
     * (fortran) code, while there are many sources that 
     * provide C-transpiled versions of that same software 
     * distribution. 
     */

    // open set boundaries.
    static constexpr auto leftbound = (f64)-0.39;
    static constexpr auto rightbound = (f64)0.57;

    // symmetrization boundary.
    static constexpr auto symmbound = (f64)0.18;

    // correction shifts.
    static constexpr auto leftbias = (f64)0.566749439387324e-1;
    static constexpr auto rightbias = (f64)0.456512608815524e-1;


    static constexpr Polynomial p(
        (f64)0.333333333333333  ,
        (f64)-0.224696413112536 ,
        (f64)0.00620886815375787,
    );

    static constexpr Polynomial q(
        (f64)1.0              ,
        (f64)-1.27408923933623,
        (f64)0.354508718369557,
    );

    if (u <= (f64)-1.0)
        return NAN;

    // direct evaluation. 
    if (u < leftbound || rightbound < u)
        return u - std::log((f64)1.0 + u);

    f64 coordinate{}; 
    f64 correction{}; 
   
    // left region.
    if (u < -symmbound) {
        coordinate = (u + (f64)0.3) / 
            (f64)0.7;
        correction = leftshift - coordinate * 
            (f64)0.3;
    }

    // right region.
    else if (u > symmbound) {
        coordinate = (f64)0.75 * u - (f64)0.25;
        correction = rightshift + h / 
            (f64)3.0; 
    }

    // central region.
    else {
        h = u;
        correction = 0.0;
    }

    // transform maps to symmetrized domain.
    const auto mobius = u / (u + (f64)2.0);
    const auto even = mobius * mobius;
    const auto rational = p(even) / q(even);

    return even * (f64)2.0 * 
        ((f64)1.0 / ((f64)1 - mobius) - mobius * 
            rational) + correction;
}


#endif
