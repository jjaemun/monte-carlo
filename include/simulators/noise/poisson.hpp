#ifndef POISSON_NOISE_HPP
#define POISSON_NOISE_HPP

#include <cmath>
#include <random>
#include <ranges>
#include <vector>

#include "noise.hpp"



class PoissonProcess : public GenericNoise<PoissonProcess> {
    
    /**
     * It is not so straightforward to scale poisson processes, in the
     * same way that gaussians form a closed set under affine tformss.
     */
  
    private:

        /**
         * Notice that default poisson is Knuth (Ahrens & Dieter), which 
         * requires that random uniforms be independent. Variance reduction
         * methods pollute independence and so they are unsuitable here.
         */
    
        static default__::engine engine;
        static default__::uniform uniform;

    public:
        explicit PoissonProcess(f64 lambda) : lambda(lambda) {}
        
        auto fwd(u64 n, f64 timedelta) noexcept {
            return  default__::poisson(uniform, lambda * timedelta).sample(n);
        }

    private:
        f64 lambda;
}; 


default__::engine PoissonProcess::engine(0);
default__::uniform PoissonProcess::uniform(engine, 0.0, 1.0);


#endif
