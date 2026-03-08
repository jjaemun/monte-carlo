#ifndef POISSON_NOISE_HPP
#define POISSON_NOISE_HPP

#include <cmath>
#include <random>
#include <ranges>
#include <vector>

#include "factory.hpp"
#include "noise.hpp"


template <typename Uniform>
class PoissonProcess : public GenericNoise<PoissonProcess<Uniform>> {
    
    /**
     * It is not so straightforward to scale poisson processes, in the same way
     * that gaussians form a closed set under affine tformss.
     */

    public:
        explicit PoissonProcess(f64 lambda, u64 seed) 
            : lambda(lambda), uniform(make_uniform(seed)) {}
        
        auto fwd(u64 n, f64 timedelta) noexcept {
 
            /**
             * Notice that default poisson is Knuth (Ahrens & Dieter), which
             * requires that random uniforms be independent. Variance reduction
             * methods pollute independence, and so they are unsuitable here.
             */

            return defaults::poisson(uniform, lambda * timedelta).sample(n);
        }

    private:
        f64 lambda;
        Uniform uniform;
}; 


#endif


// issues! reconstructing engine from seed at every call* it generates
// the same sequence. Store uniform to preserve sequence advancements?
