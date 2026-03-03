#ifndef UNIFORM_HPP 
#define UNIFORM_HPP


#include <random>
#include <utility>

#include "distribution.hpp"


template <typename RandomBitGenerator>
class Uniform final {
    
    std::uniform_real_distribution<f64> dist;

    public:
        explicit Uniform(RandomBitGenerator rng, f64 a, f64 b) 
            : rng(rng), a(a), b(b), dist(a, b) {}

        std::vector<f64> sample(u64 n) {
            std::vector<f64> samples(n);
            for (auto &sample : samples) {
                sample = dist(rng);
            }

            return samples;
        }

        auto min(void) const noexcept -> f64 { return a; }
        auto max(void) const noexcept -> f64 { return b; }

    private:
        RandomBitGenerator rng;
        f64 a, b;
};


#endif
