#ifndef STATS_EXPONENTIAL_HPP
#define STATS_EXPONENTIAL_HPP


#include "generics.hpp"
#include "random/distributions/exponential.hpp"


class ExponentialMoments : 
public GenericTheoreticMoments<ExponentialMoments> {
    public:
        template <typename Exponential>
        f64 fm(const Exponential &exponential) const noexcept {
            return (f64)1.0 / exponential.rate();
        }

        template <typename Exponential>
        f64 scm(const Exponential &exponential) const noexcept {
            const auto rate = exponential.rate();
            return (f64)1.0 / (rate * rate);
        }
    
        template <typename Exponential>
        constexpr f64 tsm(const Exponential &exponential) const noexcept {
            return (f64)2.0;
        }
       
        template <typename Exponential>
        constexpr f64 fsm(const Exponential &exponential) const noexcept {
            return (f64)9.0;
        }
};


#endif 
