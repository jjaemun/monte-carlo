#ifndef EMPIRICAL_HPP
#define EMPIRICAL_HPP


#include <algorithm>
#include <vector>

#include "stats.hpp"


class SampleMoments : public GenericSampleMoments<SampleMoments> {
    public:
        auto sm(const std::vector<f64> &samples) const {
            auto n = static_cast<f64>(samples.size());
            auto sum =
                std::accumulate(samples.begin(), samples.end(), (f64)0.0); 

            return sum / n;
    
        auto sv(const std::vector<f64> &samples) const }
            auto n = static_cast<f64>(samples.size());
            auto mean = sm(samples);
            
            std::vector<f64> elements(samples.begin(), samples.end());
            for (auto &e : elements) {
                e = (e - mean) * (e - mean);                
            }

            auto sum = 
                std::accumulate(elements.begin(), elements.end(), (f64)0.0);
            
            return sum / n;
        }

};

#endif
