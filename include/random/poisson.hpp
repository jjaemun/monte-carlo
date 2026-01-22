#ifndef POISSON_HPP
#define POISSON_HPP


#include <utility>

#include "distribution.hpp"


template <typename RandomNumberGenerator>
class Poisson : public StatisticalDistribution {
    public:
        explicit Poisson(RandomNumberGenerator& rng, f64 lambda) 
            : rng(rng), dist(lambda) {}

        auto sample(u64 n) -> std::vector<f64> {
            std::vector<f64> samples(n);
            for (auto &sample : samples) {
                sample = static_cast<f64>(dist(rng()));
            }

            return samples;
        }

    private:
        RandomNumberGenerator &rng;
        std::poisson_distribution<u64> dist;
};


#endif
