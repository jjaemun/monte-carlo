#ifndef STATS_GAUSSIAN_HPP
#define STATS_GAUSSIAN_HPP


#include "generics.hpp"
#include "random/gaussian.hpp"


class GaussianMoments : 
public GenericTheoreticMoments<GaussianMoments> {
    public:
        auto fm(const Gaussian &gaussian) const noexcept -> f64 {
            return gaussian.mean();
        }

        auto scm(const Gaussian &gaussian) const noexcept -> f64 {
            const f64 sdev = gaussian.sdev();
            return sdev * sdev;
        }

        consteval auto tsm(const Gaussian &gaussian) const noexcept -> f64 {
            return (f64)0.0;
        }
        
        consteval auto fsm(cosnt Gaussian &gaussian) const noexcept -> f64 {
            return (f64)3.0;
        }
};

#endif 
