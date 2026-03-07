#ifndef BROWNIAN_NOISE_HPP
#define BROWNIAN_NOISE_HPP

#include <cmath>
#include <random>
#include <ranges>
#include <vector>

#include "noise.hpp"


namespace {
    default__::engine engine(0);
    default__::uniform uniform(engine, 0.0, 1.0);
    default__::sampler sampler(uniform);
    default__::gaussian gauss(sampler, 0.0, 1.0);
}


class BrownianProcess : public GenericNoise<BrownianProcess> {
    
    /**
     * The dynamics of Brownian motion are fully described by means of
     * its properties. Increments are centered gaussian (with variance 
     * equal to the time interval) random variables.
     */
    
    public:
        auto fwd(u64 n, f64 timedelta) noexcept {
            std::vector<f64> increments(n);

            auto gaussians = gauss.sample(n);
            for (auto [increment, gaussian] : std::views::zip(increments, gaussians))
                increment = std::sqrt(timedelta) * gaussian;
            
            return increments;
        }
}; 



#endif
