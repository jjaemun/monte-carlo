#ifndef ANTITHETIC_HPP
#define ANTITHETIC_HPP


#include <type_traits>

#include "random/distribution.hpp"
#include "types.hpp"


class AntitheticSampler final {

    /*
     * A general form for antithetic sampling cannot be constructed in
     * sample space. 
     *
     * In order that distribution symmetry need not be assumed, it must
     * be informed of the underlying distirbution and the inverse cdf. 
     * 
     * This constraint suggests that any architecture where statistical
     * distributions preceed variance reduction strategies is therefore 
     * limited by definition of its own abstractions. At the very least
     * not without awkwardly deferring computations to accomodate all 
     * logic at an appropriate level, or by adding more code that will
     * cover the remaining cases.
     *
     * The same implication holds quasi-monte-carlo methods or stratified 
     * sampling, seeing that they also work in probability space. 
    */

    public:
        AntitheticSampler(StatisticalDistribution *dist) : dist(dist) {}
    
        std::vector<f64> sample(u64 n) override {
            std::vector<f64> antithetics{};
            antithetics.reserve(n);

            const auto half = static_cast<u64>(n / 2); 

            const auto samples = dist->sample(half);
            for (const auto &sample : samples) {
                antithetics.push_back(sample);
                antithetics.push_back(-sample);
            }

            if (n & 1) {
                antithetics.push_back(
                    dist->sample(1).front()
                );
            }

            return antithetics;
        }

    private
        StatisticalDistribution *dist;
};

#endif 
