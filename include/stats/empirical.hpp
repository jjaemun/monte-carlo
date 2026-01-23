#ifndef EMPIRICAL_HPP
#define EMPIRICAL_HPP


#include <algorithm>
#include <ranges>
#include <vector>

#include "stats.hpp"


class SampleMoments : public GenericSampleMoments<SampleMoments> {
    public:
        auto sm(const std::vector<std::vector<f64>> &samples) const {
            std::vector<f64> mean{};
            mean.reserve(samples.size());
            for (auto timestep : samples) {
                auto n = static_cast<f64>(timestep.size());
                auto sum =
                    std::accumulate(timestep.begin(), timestep.end(), (f64)0.0); 
                
                mean.emplace_back(sum / n);
            }
        
            return mean;
        }
    
        auto sv(const std::vector<std::vector<f64>> &samples) const {
            auto means = sm(samples);

            std::vector<f64> variance{};
            variance.reserve(samples.size());
            for (auto [timestep, m] : std::views::zip(samples, means)) {
                auto n = static_cast<f64>(timestep.size());
                auto sum = (f64)0.0;
                for (auto state : timestep) {
                    auto diff = state - m; 
                    sum += diff * diff;
                }
            
                variance.emplace_back(sum / (n - 1));
            }
        
            return variance;
        }

};

#endif
