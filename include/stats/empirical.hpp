#ifndef EMPIRICAL_HPP
#define EMPIRICAL_HPP


#include <algorithm>
#include <ranges>
#include <vector>

#include "stats.hpp"


class SampleMoments : public GenericSampleMoments<SampleMoments> {
    public:
        auto sm(const std::vector<std::vector<f64>> &samples) const {
            std::vector<f64> means{};
            mean.reserve(samples.size());
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
            auto means = sm(samples);
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
            for (auto lagged : std::views::iota(0, timesteps)) {
                 for (auto concurr : std::views::iota(lagged, timesteps)) {
                    auto sum = (f64)0.0;
                    for (auto path : std::views::iota(0, paths)) 
                        sum += (samples[lagged][path] - means[lagged]) * 
                            (samples[concurr][path] - means[concurr]);

                    const auto cov = sum / (static_cast<f64>(paths) - (f64)1.0);
                    
                    autocovariance[lagged][concurr] = cov;
                    autocovariance[concurr][lagged] = cov;
                }
            }
            
            return autocovariance;
        }
};

#endif
