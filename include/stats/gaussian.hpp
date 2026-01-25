#ifndef STATS_GAUSSIAN_HPP
#define STATS_GAUSSIAN_HPP


#include "generics.hpp"
#include "random/gaussian.hpp"


class GaussianMoments : 
public GenericTheoreticMoments<GaussianMoments> {
    public:
        template <typename Gaussian>
        f64 fm(const Gaussian &gaussian) const noexcept {
            return gaussian.mean();
        }

        template <typename Gaussian>
        f64 scm(const Gaussian &gaussian) const noexcept {
            const f64 sdev = gaussian.sdev();
            return sdev * sdev;
        }
    
        template <typename Gaussian>
        constexpr f64 tsm(const Gaussian &gaussian) const noexcept {
            return (f64)0.0;
        }
       
        template <typename Gaussian>
        constexpr f64 fsm(const Gaussian &gaussian) const noexcept {
            return (f64)3.0;
        }
};

#endif 
