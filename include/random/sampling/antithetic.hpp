#ifndef ANTITHETIC_HPP
#define ANTITHETIC_HPP


#include <type_traits>

#include "random/distribution.hpp"
#include "sampler.hpp"
#include "types.hpp"


class AntitheticSampler final : public Sampler {
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
