#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP


#include <utility>

#include "distribution.hpp"


template <typename RandomNumberGenerator>
class Gaussian : public StatisticalDistribution {
    public:
        explicit Gaussian(RandomNumberGenerator& rng, f64 mu, f64 sigma) 
            : rng(rng), dist(mu,sigma) {}

        auto sample(u64 n) -> std::vector<f64> {
            std::vector<f64> samples(n);
            for (auto &sample : samples) {
                sample = dist(rng());
            }

            return samples;
        }

    private:
        RandomNumberGenerator &rng;
        std::normal_distribution<f64> dist;
};


#endif
