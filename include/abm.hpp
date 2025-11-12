#ifndef ARITHMETIC_BROWNIAN_MOTION_HPP
#define ARITHMETIC_BROWNIAN_MOTION_HPP


#include <cmath>

#include "simulator.hpp"
#include "configs.hpp"
#include "context.hpp"



template <typename T>
class ArithmeticBrownianMotion : public Simulator<ArithmeticBrownianMotion<T>> {

    static_assert(std::is_floating_point_v<T>);

    public:
        ArithmeticBrownianMotion(const abm::config<T> &config) 
            : config(config) {}

        auto sim(const context &ctx) -> array2d_t<T> const noexcept {
            const T dt = (ctx.t - ctx.s) 
                / static_cast<T>(ctx.timesteps);
            const auto drift = array2d_t<T>::Constant(
                ctx.paths, ctx.timesteps, config.mu * dt);
            const auto diffusion = config.sigma * random::normal(
                ctx.paths, ctx.timesteps, 0, std::sqrt(dt));
            const auto ds = drift + diffusion;
           
            array2d_t<T> states(ctx.paths, ctx.timesteps + 1);
            states.col(0) = array2d_t<T>::Constant(ctx.paths, 1, config.spot);
            states.block(0, 1, ctx.paths, ctx.timesteps) = 
                states.col(0).rowwise() + ds.rowwise().cumsum();

            return states;
        }

    private:
        abm::config<T> &config;
};




#endif 
