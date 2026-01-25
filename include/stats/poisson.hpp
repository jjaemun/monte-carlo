#ifndef STATS_GAUSSIAN_HPP
#define STATS_GAUSSIAN_HPP


#include <cmath>

#include "generics.hpp"
#include "random/gaussian.hpp"


class PoissonMoments : 
public GenericTheoreticMoments<PoissonMoments> {
    public:
        f64 fm(const Poisson &poisson) const noexcept {
            return poisson.intensity();
        }

        f64 scm(const Poisson &poisson) const noexcept {
            return poisson.intensity();
        }

        f64 tsm(const Poisson &poisson) const noexcept {
            return (f64)1.0 / 
                std::sqrt(poisson.intensity());
        }
        
        f64 fsm(const Poisson &poisson) const noexcept {
            return (f64)3.0 + ((f64)1.0 / 
                poisson.intensity());
        }
};

#endif 
