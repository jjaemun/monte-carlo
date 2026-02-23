#ifndef POISSON_HPP
#define POISSON_HPP


#include <cmath>
#include <ranges>
#include <vector>

#include "distribution.hpp"


#define ERROR(msg) (std::cerr << "error! " << msg << std::endl; std::exit(-999))


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
            // heuristic for uniform sample size.
            const auto ssize = static_cast<u64>(lambda) + (u64)1;
   
            // product space threshold.
            const auto threshold = std::exp(-lambda);

            auto knuth = [=](void) const noexcept -> f64 {
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
