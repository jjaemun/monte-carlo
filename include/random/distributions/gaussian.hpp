#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP


#include <vector>
#include <ranges>

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
            for (auto& [gaussian, uniform] : std::views::zip(gaussians, uniforms) 
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
        explicit GaussianBoxMuller(f64 mu, f64 sigma) 
            : mu(mu), sigma(sigma) {}

        std::vector<f64> sample(const std::vector<f64> &uniforms) const noexcept {
            std::vector<f64> gaussians{};
            gaussians.reserve(uniforms.size());

            for (auto& pair : uniforms | std::views::chunk(2)) {
                const auto factor = 
                    std::sqrt((f64)-2.0 * 
                        std::log(pair.front()));
                const auto theta = 
                    (f64)2.0 * std::numbers::pi * 
                        pair.back();

                gaussians.push_back(sigma * factor * std::cos(theta) + mu);
                gaussians.push_back(sigma * factor * std::sin(theta) + mu);
            }

            return gaussians;
        }
        
        auto mean(void) const noexcept -> f64 { return mu; }
        auto sdev(void) const noexcept -> f64 { return sigma; }

    private:
        f64 mu, sigma;
};


#endif


// check Beasly and Springer, 1977. (PPND of AS 111)
