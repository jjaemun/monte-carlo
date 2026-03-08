#ifndef BROWNIAN_NOISE_HPP
#define BROWNIAN_NOISE_HPP

#include <cmath>
#include <random>
#include <ranges>
#include <vector>

#include "factory.hpp"
#include "noise.hpp"


class BrownianProcess : public GenericNoise<BrownianProcess> {
    
    /**
     * The dynamics of Brownian motion are fully described by means of
     * its properties. Increments are centered gaussian (with variance 
     * equal to the time interval) random variables.
     */
    
    public:
        explicit BrownianProcess(u64 seed) : gauss(make_gaussian(seed)) {}

        auto fwd(u64 n, f64 timedelta) noexcept {
            std::vector<f64> increments(n);

            auto gaussians = gauss.sample(n);
            for (auto [increment, gaussian] : std::views::zip(increments, gaussians))
                increment = std::sqrt(timedelta) * gaussian;
            
            return increments;
        }

    private:
        defaults::gaussian gauss;
}; 



#endif
