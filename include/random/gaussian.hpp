#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP


#include <utility>

#include "distribution.hpp"


template <typename RandomNumberGenerator>
class Gaussian : public StatisticalDistribution {
    public:
        explicit Gaussian(RandomNumberGenerator& rng, f64 mu, f64 sigma) 
            : rng(rng), dist(mu,sigma) {}

        auto sample(u64 n, u64 m) override {
            std::vector<std::vector<f64>> samples(n, std::vector<f64>(m));
            for (auto &row: samples) {
                for (auto &column : row) {
                    sample = dist(rng());
                }
            }

            return samples;
        }

    private:
        RandomNumberGenerator &rng;
        std::normal_distribution<f64> dist;
};


#endif
