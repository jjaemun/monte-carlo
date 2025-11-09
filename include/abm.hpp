#ifndef ARITHMETIC_BROWNIAN_MOTION_HPP
#define ARITHMETIC_BROWNIAN_MOTION_HPP


#include <cmath>

#include "simulator.hpp"
#include "configs.hpp"
#include "contexts.hpp"



template <typename T>
class ArithmeticBrownianMotion : public Simulator<ArithmeticBrownianMotion<T>> {

    static_assert(std::is_floating_point_v<T>);

    public:
        ArithmeticBrownianMotion(const diffusion::context<T> &ctx, const abm::config<T> &config) 
            : ctx(ctx), config(config) {}

        auto sim(const T s, const T t) -> ARRAY2D<T> {
            const T dt = (t - s) / T(ctx.timesteps);

            const auto drift = ARRAY2D<T>::Constant(
                ctx.paths, ctx.timesteps, config.mu * dt);
            const auto diffusion = config.sigma 
                * ctx.nn(0, std::sqrt(dt));
            const auto ds = drift + diffusion;
           
            ARRAY2D<T> states(ctx.paths, ctx.timesteps + 1);
            states.col(0) = ARRAY2D<T>::Constant(ctx.paths, 1, config.spot);
            states.block(0, 1, ctx.paths, ctx.timesteps) = 
                states.col(0).rowwise() + ds.rowwise().cumsum();

            return states;
        }

    private:
        diffusion::context<T> &ctx;
        abm::config<T> &config;
};




#endif 
