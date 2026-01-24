#ifndef EMPIRICAL_HPP
#define EMPIRICAL_HPP


#include <algorithm>
#include <cmath>
#include <ranges>
#include <vector>

#include "generics.hpp"


class SampleMoments : public GenericSampleMoments<SampleMoments> {
    public:
        auto sm(const std::vector<std::vector<f64>> &samples) const {
            std::vector<f64> means{};
            means.reserve(samples.size());
            for (const auto &timestep : samples) {
                auto n = static_cast<f64>(timestep.size());
                auto sum =
                    std::accumulate(timestep.begin(), timestep.end(), (f64)0.0); 
                
                means.emplace_back(sum / n);
            }
        
            return means;
        }
    
        auto sv(const std::vector<std::vector<f64>> &samples) const {
            std::vector<f64> variance{};
            variance.reserve(samples.size());
            const auto means = sm(samples);
            for (const auto& [timestep, mean] : std::views::zip(samples, means)) {
                auto n = static_cast<f64>(timestep.size());
                auto sum = (f64)0.0;
                for (auto state : timestep) {
                    auto diff = state - mean; 
                    sum += diff * diff;
                }
            
                variance.emplace_back(sum / (n - 1));
            }
        
            return variance;
        }

        auto sc(const std::vector<std::vector<f64>> &samples) const {
            std::vector<std::vector<f64>> autocovariance(samples.size());
            for (auto &v : autocovariance) {
                v.resize(samples.size()); 
            }
       
            const auto timesteps = samples.size();
            const auto paths = samples.front().size();

            const auto means = sm(samples);
            for (auto s : std::views::iota(0, timesteps)) {
                 for (auto t : std::views::iota(s, timesteps)) {
                    auto sum = (f64)0.0;
                    for (auto path : std::views::iota(0, paths)) 
                        sum += (samples[s][path] - means[s]) * 
                            (samples[t][path] - means[t]);

                    const auto cov = sum / (static_cast<f64>(paths) - (f64)1.0);
                    
                    autocovariance[s][t] = cov;
                    autocovariance[t][s] = cov;
                }
            }
            
            return autocovariance;
        }
};

class SamplePearsonAutocorrelation : 
public GenericSampleAutocorrelation<PearsonAutocorrelation> {
    public:
        auto spa(const std::vector<std::vector<f64>> &samples) const {
            std::vector<std::vector<f64>> autocorrelation(samples.size());
            for (auto &v : autocorrelation) {
                v.resize(samples.size()); 
            }
       
            const auto timesteps = samples.size();
            const auto paths = samples.front().size();

            const auto variance = empirical.variance(samples);
            const auto autocovariance = empirical.autocovariance(samples);

            for (auto s : std::views::iota(0, timesteps)) {
                 for (auto t : std::views::iota(s, timesteps)) {
                    const auto denom = std::sqrt(variance[s]) * 
                        std::sqrt(variance[t]);

                    f64 corr{};
                    if (denom > 0.0)
                        corr = autocovariance[s][t] / denom; 
                        
                    autocorrelation[s][t] = corr;
                    autocorrelation[t][s] = corr;
                }
            }

            return autocorrelation;
        }

    private:
        inline SampleMoments empirical{};
};


class SpearmanSampleAutocorrelation : 
public GenericSampleAutocorrelation<PearsonAutocorrelation> {

};


#endif
