#ifndef ARITHMETIC_BROWNIAN_MOTION_HPP
#define ARITHMETIC_BROWNIAN_MOTION_HPP


#include <cmath>

#include "simulator.hpp"
#include "configs.hpp"
#include "contexts.hpp"


// entirely experimental. just something tangible to look at while I develop the general architecture



template <typename T>
class ArithmeticBrownianMotion : public Simulator<ArithmeticBrownianMotion<T>> {

    static_assert(std::is_floating_point_v<T>);

    public:
        ArithmeticBrownianMotion(const abm::config<T> &config) 
            : config(config) {}

        auto sim(const context &ctx) -> array2d_t<T> {
            const auto drift = array2d_t<T>::Constant(
                ctx.paths, ctx.timesteps, config.mu * ctx.dt);
            const auto diffusion = config.sigma 
                * ctx.nn(0, std::sqrt(ctx.dt));
            const auto ds = drift + diffusion;
           
            ARRAY2D<T> states(ctx.paths, ctx.timesteps + 1);
            states.col(0) = array2d_t<T>::Constant(ctx.paths, 1, config.spot);
            states.block(0, 1, ctx.paths, ctx.timesteps) = 
                states.col(0).rowwise() + ds.rowwise().cumsum();

            return states;
        }

    private:
        abm::config<T> &config;
};




#endif 
