#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP

#include <random>
#include <utility>

#include "distribution.hpp"


template <typename RandomNumberGenerator>
class Gaussian : public StatisticalDistribution {
    
    std::normal_distribution<f64> dist;

    public:
        explicit Gaussian(RandomNumberGenerator& rng, f64 mu, f64 sigma) 
            : rng(rng), mu(mu), sigma(sigma), dist(mu,sigma) {}

        auto sample(u64 n) override {
            std::vector<f64> samples(n);
            for (auto &sample : samples) {
                sample = dist(rng());
            }

            return samples;
        }

        auto mean(void) const noexcept -> f64 { return mu; }
        auto sdev(void) const noexcept -> f64 { return sigma; }

    private:
        RandomNumberGenerator &rng;
        f64 mu, sigma;
};


#endif
