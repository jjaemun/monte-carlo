#ifndef GEOMETRIC_BROWNIAN_MOTION_HPP
#define GEOMETRIC_BROWNIAN_MOTION_HPP


#include "simulator.hpp"
#include "configs.hpp"
#include "context.hpp"


template <typename T>
class GeometricBrownianMotion : public Simulator<GeometricBrownianMotion<T>> {

    static_assert(std::is_floating_point_v<T>);

    public:
        GeometricBrownianMotion(const gbm::config<T> &config) 
            : config(config) {}

        auto sim(const context<T> &ctx) const -> array2d_t<T> {
            const T dt = (ctx.t - ctx.s) 
                / static_cast<T>(ctx.timesteps);
            const auto drift = (config.mu - 0.5 * config.sigma * 
                config.sigma)* dt;
            const auto diffusion = config.sigma * rng::normal(
                ctx.paths, ctx.timesteps, 0.0, std::sqrt(dt));
            auto ds = (drift + diffusion).eval();
           
            array2d_t<T> states(ctx.paths, ctx.timesteps + 1);
            states.col(0) = array2d_t<T>::Constant(
                ctx.paths, 1, 1);

            for (index_t j = 1; j < states.cols(); ++j) {
                states.col(j) = states.col(j - 1) + ds.col(j - 1);
            }

            return config.spot * exp(states);
        }

    private:
        const gbm::config<T> &config;
};




#endif 
