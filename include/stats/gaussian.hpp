#ifndef STATS_GAUSSIAN_HPP
#define STATS_GAUSSIAN_HPP


#include "generics.hpp"
#include "random/gaussian.hpp"


class GaussianMoments : 
public GenericTheoreticMoments<GaussianMoments> {
    public:
        f64 fm(const Gaussian &gaussian) const noexcept {
            return gaussian.mean();
        }

        f64 scm(const Gaussian &gaussian) const noexcept {
            const f64 sdev = gaussian.sdev();
            return sdev * sdev;
        }

        constexpr f64 tsm(const Gaussian &gaussian) const noexcept {
            return (f64)0.0;
        }
        
        constexpr f64 fsm(const Gaussian &gaussian) const noexcept {
            return (f64)3.0;
        }
};

#endif 
