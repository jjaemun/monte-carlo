#ifndef EMPIRICAL_HPP
#define EMPIRICAL_HPP


#include <numeric>
#include <cmath>
#include <ranges>
#include <vector>

#include "generics.hpp"
#include "types.hpp"


class SampleDistributionMoments : 
public GenericSampleMoments<SampleDistributionMoments> {
    public: 
        auto sm(const std::vector<f64> &samples) {
            const auto n = static_cast<f64>(samples.size());
            const auto sum =
               std::accumulate(samples.begin(), samples.end(), (f64)0.0);

            return sum / n;
        }

        auto sv(const std::vector<f64> &samples) {
            const auto n = static_cast<f64>(samples.size());
            const auto mean = sm(samples);

            auto sum = (f64)0.0;
            for (auto sample : samples) {
                auto diff = sample - mean;
                sum += diff * diff;
            }
            
            return sum / (n - (f64)1.0);
        }

        auto ss(const std::vector<f64> &samples) {
            const auto n = static_cast<f64>(samples.size());
            const auto mean = sm(samples);
            const auto variance = sv(samples);

            if (variance <= (f64)0.0)
                return (f64)0.0;
           
            auto sum = (f64)0.0;
            for (auto sample : samples) {
                auto diff = sample - mean;
                sum += diff * diff * diff;
            }
                
            const auto norm = std::pow(variance, (f64)1.5);
            return sum / (n * norm);
        }

        auto sk(const std::vector<f64> &samples) {
            const auto n = static_cast<f64>(samples.size());
            const auto mean = sm(samples);
            const auto variance = sv(samples);

            if (variance <= (f64)0.0)
                return (f64)0.0;
           
            auto sum = (f64)0.0;
            for (auto sample : samples) {
                auto diff = sample - mean;
                sum += diff * diff *
                    diff * diff;
            }
                
            const auto norm = std::pow(variance, (f64)2.0);
            return sum / (n * norm);
        }
};


class SampleMoments : public GenericSampleMoments<SampleMoments> {
    public:
        auto sm(const std::vector<std::vector<f64>> &samples) {
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
    
        auto sv(const std::vector<std::vector<f64>> &samples) {
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
            
                variance.emplace_back(sum / (n - (f64)1.0));
            }
        
            return variance;
        }

        auto sc(const std::vector<std::vector<f64>> &samples) {
            std::vector<std::vector<f64>> autocovariance(samples.size());
            for (auto &v : autocovariance) {
                v.resize(samples.size()); 
            }
       
            const auto timesteps = samples.size();
            const auto paths = samples.front().size();

            const auto means = sm(samples);
            for (auto s : std::views::iota((u64)0, timesteps)) {
                 for (auto t : std::views::iota(s, timesteps)) {
                    auto sum = (f64)0.0;
                    for (auto path : std::views::iota((u64)0, paths)) 
                        sum += (samples[s][path] - means[s]) * 
                            (samples[t][path] - means[t]);

                    const auto cov = sum / (static_cast<f64>(paths) - (f64)1.0);
                    
                    autocovariance[s][t] = cov;
                    autocovariance[t][s] = cov;
                }
            }
            
            return autocovariance;
        }
    
        auto ss(const std::vector<std::vector<f64>> &samples) {
            std::vector<f64> skewness{};
            skewness.reserve(samples.size());

            const auto means = sm(samples);
            const auto variance = sv(samples);

            for (const auto& [timestep, mean, var] :
                    std::views::zip(samples, means, variance)) {
                const auto paths = static_cast<f64>(timestep.size());

                if (var <= (f64)0.0) {
                    skewness.emplace_back((f64)0.0);
                    continue;
                }
                
                auto sum = (f64)0.0;
                for (auto state : timestep) {
                    auto diff = state - mean;
                    sum += diff * diff * diff;
                }
          
                // normalizing base.
                const auto norm = std::pow(var, (f64)1.5);
                skewness.emplace_back(sum / (paths * norm));
            }

            return skewness;
        }        

        auto sk(const std::vector<std::vector<f64>> &samples) {
            std::vector<f64> kurtosis{};
            kurtosis.reserve(samples.size());

            const auto means = sm(samples);
            const auto variance = sv(samples);

            for (const auto& [timestep, mean, var] :
                    std::views::zip(samples, means, variance)) {
                const auto paths = static_cast<f64>(timestep.size());

                if (var <= (f64)0.0) {
                    kurtosis.emplace_back((f64)0.0);
                    continue;
                }
                
                auto sum = (f64)0.0;
                for (auto state : timestep) {
                    auto diff = state - mean;
                    sum += diff * diff * 
                        diff * diff;
                }
          
                // normalizing base.
                const auto norm = std::pow(var, (f64)2.0);
                kurtosis.emplace_back(sum / (paths * norm));
            }

            return kurtosis;
        }

};

class SamplePearsonAutocorrelation : 
public GenericSampleAutocorrelation<SamplePearsonAutocorrelation> {
    public:
        auto sac(const std::vector<std::vector<f64>> &samples) {
            std::vector<std::vector<f64>> autocorrelation(samples.size());
            for (auto &v : autocorrelation) {
                v.resize(samples.size()); 
            }
       
            const auto timesteps = samples.size();
            const auto paths = samples.front().size();

            const auto variance = empirical.variance(samples);
            const auto autocovariance = empirical.autocovariance(samples);

            for (auto s : std::views::iota((u64)0, timesteps)) {
                 for (auto t : std::views::iota(s, timesteps)) {
                    const auto norm= std::sqrt(variance[s]) * 
                        std::sqrt(variance[t]);

                    f64 corr{};
                    if (norm > 0.0)
                        corr = autocovariance[s][t] / norm; 
                        
                    autocorrelation[s][t] = corr;
                    autocorrelation[t][s] = corr;
                }
            }

            return autocorrelation;
        }

    private:
        SampleMoments empirical{};
};


class SampleSpearmanAutocorrelation : 
public GenericSampleAutocorrelation<SampleSpearmanAutocorrelation> {};


#endif
