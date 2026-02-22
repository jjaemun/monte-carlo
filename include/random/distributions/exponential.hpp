#ifndef EXPONENTIAL_HPP
#define EXPONENTIAL_HPP


#include <cmath>
#include <vector>
#include <ranges>

#include "distribution.hpp"


#define ERROR(msg) (std::cerr << "error! " << msg << std::endl; std::exit(-999))


template <typename Sampler>
class ExponentialDistribution : public StatisticalDistribution {


    public:
        explicit ExponentialDistribution(Sampler sampler, f64 lambda) 
            : sampler(std::move(sampler)), lambda(lambda) {
                if (lambda <= 0) 
                    ERROR("lambda must be positive.");
            }

    
        std::vector<f64> sample(u64 n) override {
            std::vector<f64> exponentials(n);

            const auto uniforms = sampler.sample(n);
            for (auto& [exponential, uniform] : std::views::zip(exponentials, uniforms))
                exponential = -std::log(uniform) / lambda;

            return exponentials;
        }

        auto rate(void) const noexcept -> f64 { return lambda; } 

    private:
        Sampler sampler;
        f64 lambda;

};


#undef ERROR


#endif 
