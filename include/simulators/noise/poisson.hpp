#ifndef POISSON_NOISE_HPP
#define POISSON_NOISE_HPP

#include <cmath>
#include <random>
#include <ranges>
#include <vector>

#include "noise.hpp"


template <typename Poisson>
class PoissonProcess : public GenericNoise<PoissonProcess<Poisson>> {
    
    /**
     * It is not so straightforward to scale poisson processes, in the same
     * way that gaussians form a closed set under affine tformss.
     */

    public:
        explicit PoissonProcess(u64 seed, f64 lambda) : lambda(lambda), seed(seed)) {}
        
        auto fwd(u64 n, f64 timedelta) noexcept {
 
            /**
             * Notice that default poisson is Knuth (or Ahrens & Dieter), which
             * requires that random uniforms be independent. Variance reduction
             * methods pollute independence and so they are unsuitable here.
             */

            return make_poisson(seed, lambda * timedelta).sample(n);
        }

    private:
        u64 seed;
        f64 lambda;
}; 


#endif


// issues! reconstructing engine from seed at every call, it generates
// the same sequence. Store uniform to preserve sequence advancements?
