#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP


#include <random>
#include <ranges>
#include <utility>


#include "sampling/sampler.hpp"
#include "distribution.hpp"
#include "kernels/norminv.hpp"


template <typename Sampler>
class Gaussian : public StatisticalDistribution {

    public:
        explicit Gaussian(Sampler sampler, f64 mu, f64 sigma) 
            : sampler(std::move(sampler)), mu(mu), sigma(sigma) {}

        std::vector<f64> sample(u64 n) override {
            std::vector<f64> gaussians(n);

            const auto uniforms = sampler.sample(n);
            for (auto& [uniform, gaussian] : std::views::zip(uniforms, gaussians) 
                gaussian = sigma * norminv(uniform) + mu;
            
            return gaussians;
        }

        auto mean(void) const noexcept -> f64 { return mu; }
        auto sdev(void) const noexcept -> f64 { return sigma; }

    private:
        Sampler sampler;
        f64 mu, sigma;
};


class GaussianBoxMuller final {
    public:
        std::vector<f64> 
        operator()(const std::vector<f64> &uniforms) const {
            std::vector<f64> samples{};
            samples.reserve(uniforms.size());

            for (auto& pair : uniforms | std::views::chunk(2)) {
                const auto u1 = pair.front();
                const auto u2 = pair.back();

                const auto factor = 
                    std::sqrt((f64)-2.0 * std::log(u1));
                const auto theta = 
                    (f64)2.0 * std::numbers::pi * u2;

                samples.push_back(factor * std::cos(theta));
                samples.push_back(factor * std::sin(theta));
            }

            return samples;
        }
};


#endif


// check Beasly and Springer, 1977. (PPND of AS 111)
