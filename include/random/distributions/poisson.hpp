#ifndef POISSON_HPP
#define POISSON_HPP


#include <cstdlib>
#include <cmath>
#include <iostream>

#include "distribution.hpp"


#define ERROR(msg) (std::cerr << "error! " << msg << std::endl)


template <typename Sampler>
class PoissonKnuth final : public StatisticalDistribution {

    /**
     * The method is in fact due to Ahrens and Dieter, although the
     * present work uses the well-known definition in Knuth (1969).
     */

    public:
        explicit PoissonKnuth(Sampler sampler, f64 lambda)
            : sampler(std::move(sampler)), lambda(lambda) {
                if (lambda <= 0) 
                    ERROR("lambda must be positive.");
            }
        
        std::vector<f64> sample(u64 n) override {
            // product space threshold.
            const auto threshold = std::exp(-lambda);
            
            // heuristic for uniform sample size.
            const auto ssize = (u64)1 + 
                static_cast<u64>(lambda);

            auto knuth = [&](void) noexcept -> f64 {
            
                /**
                 * To simplify matters, the inequality is evaluated in log-
                 * space. The idea is that we compute the product of uniform
                 * (independent) samples u1, u2, ... until 
                
                                u1 · ... · um <= exp(-lambda) 

                 * then poisson <- m - 1. On average this requires generating
                 * lambda + 1 uniform deviates (Knuth, 1969), so its a method 
                 * suited for low intensity poisson processes.
                 */

                auto product = (f64)1.0;
                auto count = (u64)0;
        
                while (product > threshold) {
                    const auto uniforms = sampler.sample(ssize);
                    for (auto uniform : uniforms) {
                        product *= uniform;
                        count++;

                        if (product <= threshold)
                            return static_cast<f64>(count - 1);
                    }
                }
                std::unreachable();
            };

            std::vector<f64> poissons(n);
            for (auto &poisson : poissons) {
                poisson = knuth();
            }

            return poissons;
        }

        auto intensity(void) const noexcept -> f64 { return lambda; }

    private:
        Sampler sampler;
        f64 lambda;
};


#undef ERROR


#endif

// TODO: implement Ahrens & Dieter and (normal) transform rejection.

