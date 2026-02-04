#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP

#include <random>
#include <utility>

#include "distribution.hpp"
#include "transforms/tform.hpp"


template <typename RandomNumberGenerator>
class Gaussian : public StatisticalDistribution {
    
    std::normal_distribution<f64> dist;

    public:
        explicit Gaussian(RandomNumberGenerator& rng, f64 mu, f64 sigma) 
            : rng(rng), mu(mu), sigma(sigma), dist(mu,sigma) {}

        std::vector<f64> sample(u64 n) override {
            std::vector<f64> samples(n);
            for (auto &sample : samples) {
                sample = dist(rng);
            }

            return samples;
        }

        auto mean(void) const noexcept -> f64 { return mu; }
        auto sdev(void) const noexcept -> f64 { return sigma; }

    private:
        RandomNumberGenerator &rng;
        f64 mu, sigma;
};


class GaussianPolarBoxMuller final {
    public:
        std::vector<f64> 
        operator()(const std::vector<f64> &uniforms) const noexcept {
            const u64 n = uniforms.size();

            std::vector<f64> samples{};
            samples.reserve(n);

            for (auto& pair : uniforms | std::views::chunk(2)) {
                const auto u1 = pair.front();
                const auto u2 = pair.back();

                const auto radius = 
                    std::sqrt((f64)-2.0 * std::log(u1));
                const auto theta = 
                    (f64)2.0 * std::numbers::pi * u2;

                samples.push_back(radius * std::cos(theta));
                samples.push_back(radius * std::sin(theta));
            }

            return samples;
        }
};


#endif
