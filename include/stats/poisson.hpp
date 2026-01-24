#ifndef STATS_GAUSSIAN_HPP
#define STATS_GAUSSIAN_HPP


#include <cmath>

#include "generics.hpp"
#include "random/gaussian.hpp"


class PoissonMoments : 
public GenericTheoreticMoments<PoissonMoments> {
    public:
        auto fm(const Poisson &poisson) const noexcept -> f64 {
            return poisson.intensity();
        }

        auto scm(const Poisson &poisson) const noexcept -> f64 {
            return poisson.intensity();
        }

        auto tsm(const Poisson &poisson) const noexcept -> f64 {
            return (f64)1.0 / std::sqrt(poisson.intensity());
        }
        
        auto fsm(const Poisson &poisson) const noexcept -> f64 {
            return (f64)3.0 + ((f64)1.0 / poisson.intensity());
        }
};

#endif 
