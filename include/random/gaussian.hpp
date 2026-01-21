#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP


#include <utility>

#include "distribution.hpp"


template <typename Class>
class Gaussian : public StatisticalDistribution {
    public:
        Gaussian(const Class& rng, f64 mu, f64 sigma) 
            : rng(rng), dist(mu,sigma) {}

        auto sample(u64 n) -> std::vector<f64> {
            std::vector<f64> variates(n);
            for (auto &i : std::views::iota(0, n)) {
                variates[i] = dist(rng());
            }

            return variates;
        }

    private:
        Class &rng;
        std::normal_distribution<f64> dist;
};


#endif
