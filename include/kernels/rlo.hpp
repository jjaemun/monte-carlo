#ifndef RLOGONE_HPP 
#define RLOGONE_HPP 


#include <cmath>

#include "approximation/approx.hpp"
#include "types.hpp"


[[nodiscard]]
#if defined(__GNUC__) || defined(__clang__)
__attribute__((hot, always_inline))
#endif
inline f64 __rlog_one(const f64 u) noexcept {

    /**
          ALGO. 708, TOMS (Didonato & Morris, 1992)
              VOL. 18, NO. 3.

        ~ Significant Digit Computations of the Incomplete 
            Beta Function Ratios ~
        
     * Evaluates the function 

                  ƒ(u) =  u - log(1 + u).
     
     * Issues arise for small u, where the linear terms
     * cancel, leading to catastrofic cancellation when
     * evaluated directly in floating point arithmetic.
        
     * Now, in order that stability be preserved over
     * the problematic interval we use a minimax rational
     * approximation. This interval is a chosen (to 
     * balance errors) open set where smallness of u is 
     * known to cause fp ouchies (cancellation dominates
     * fp error). 
     
     * Although the rational approximation is global on 
     * the interval, it is split into regions. Each then 
     * uses corrections, in the form of a minimax linear
     * bias to flatten relative errors. A region-local
     * affine coordinate is used to condition them.
     
     * It is important to note that a (symmetry-inducing)
     * Mobius transform is used to keep the argument finite
     * as u -> -1,
     
                      r = u / (u + 2).

     * However, it induces near odd behavior and hence,
     * the apprximation is instead evaluated under a 
     * quadratic form
            
                         t = r * r.
       
     * It therefore symmetrizes the error, bounds the 
     * variable tighter, and improves conditioning, while
     * being more efficient. 
     */


    // open set boundaries.
    static constexpr auto leftbound = (f64)-0.39;
    static constexpr auto rightbound = (f64)0.57;

    // symmetrization boundary.
    static constexpr auto symmbound = (f64)0.18;

    // correction shifts.
    static constexpr auto leftshift = (f64)0.566749439387324e-1;
    static constexpr auto rightshift = (f64)0.456512608815524e-1;


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
        coordinate = (f64)0.75 * u - 
            (f64)0.25;
        correction = rightshift + coordinate / 
            (f64)3.0; 
    }

    // central region.
    else {
        coordinate = u;
        correction = (f64)0.0;
    }

    // transform to symmetrized domain.
    const auto mobius = u / (u + (f64)2.0);
    const auto even = mobius * mobius;
    const auto rational = p(even) / q(even);

    return even * (f64)2.0 * 
        ((f64)1.0 / ((f64)1 - mobius) - mobius * 
            rational) + correction;
}


using rlog1 = __rlog_one;

#endif
