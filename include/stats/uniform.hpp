#ifndef STATS_UNIFORM_HPP
#define STATS_UNIFORM_HPP


#include "generics.hpp"
#include "random/distributions/uniform.hpp"


class UniformMoments : 
public GenericTheoreticMoments<UniformMoments> {
    public:
        template <typename Uniform>
        f64 fm(const Uniform &uniform) const noexcept {
            return (uniform.max() + uniform.min()) 
                / (f64)2.0;
        }

        template <typename Uniform>
        f64 scm(const Uniform &uniform) const noexcept {
            const auto support = 
                (uniform.max() - uniform.min());

            return (support * support) / (f64)12.0;
        }
    
        template <typename Uniform>
        constexpr f64 tsm(const Uniform &uniform) const noexcept {
            return (f64)0.0;
        }
       
        template <typename Uniform>
        constexpr f64 fsm(const Uniform &uniform) const noexcept {
            return (f64)3.0 -(f64)6.0 / (f64)5.0;
        }
};


#endif 
