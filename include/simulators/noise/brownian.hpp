#ifndef BROWNIAN_HPP
#define BROWNIAN_HPP

#include <cmath>
#include <random>
#include <ranges>
#include <vector>

#include "noise.hpp"


namespace {
    static defaults__::engine engine(0);
    static defaults__::uniform uniform(engine, 0.0, 1.0);
    static defaults__::sampler sampler(uniform);
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

    private:
        static defaults__::gaussian gauss;
}; 


defaults__::gaussian BrownianProcess::gauss(sampler, 0.0, 1.0);


#endif
