#ifndef STATS_POISSON_HPP
#define STATS_POISSON_HPP


#include <cmath>

#include "generics.hpp"
#include "random/gaussian.hpp"


class PoissonMoments : 
public GenericTheoreticMoments<PoissonMoments> {
    public:
        template <typename Poisson>
        f64 fm(const Poisson &poisson) noexcept {
            return poisson.intensity();
        }

        template <typename Poisson>
        f64 scm(const Poisson &poisson) noexcept {
            return poisson.intensity();
        }

        template <typename Poisson>
        f64 tsm(const Poisson &poisson) noexcept {
            return (f64)1.0 / 
                std::sqrt(poisson.intensity());
        }
        
        template <typename Poisson>
        f64 fsm(const Poisson &poisson) noexcept {
            return (f64)3.0 + ((f64)1.0 / 
                poisson.intensity());
        }
};

#endif 
