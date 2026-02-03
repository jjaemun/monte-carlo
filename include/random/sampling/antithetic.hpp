#ifndef ANTITHETIC_HPP
#define ANTITHETIC_HPP


#include "sampler.hpp"


class AntitheticSampler final : public Sampler {
    public:
        explicit AntitheticSampler(StatisticalDistribution *dist) 
            : dist(dist) {}
    
        std::vector<f64> sample(u64 n) override {
            std::vector<f64> antithetics{};
            antithetics.reserve(n);

            const auto half = n / (u64)2; 

            const auto samples = dist->sample(half);
            for (const auto &sample : samples) {
                antithetics.push_back(sample);
                antithetics.push_back(-sample);
            }

            if (n & 1) 
                antithetics.push_back(dist->sample(1).front());

            return antithetics;
        }

    private
        StatisticalDistribution *dist;
};

#endif 
