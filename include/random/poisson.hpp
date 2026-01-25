#ifndef POISSON_HPP
#define POISSON_HPP


#include <random>

#include "distribution.hpp"


template <typename RandomNumberGenerator>
class Poisson : public StatisticalDistribution {
        
    std::poisson_distribution<u64> dist;

    public:
        explicit Poisson(RandomNumberGenerator& rng, f64 lambda) 
            : rng(rng), lambda(lambda), dist(lambda) {}

        auto sample(u64 n) override {
            std::vector<f64> samples(n);
            for (auto &sample : samples) {
                sample = static_cast<f64>(dist(rng()));
            }

            return samples;
        }

        auto intensity(void) const noexcept -> f64 { return lambda; }

    private:
        RandomNumberGenerator &rng;
        f64 lambda;
};


#endif
