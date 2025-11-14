#ifndef ARITHMETIC_BROWNIAN_MOTION_HPP
#define ARITHMETIC_BROWNIAN_MOTION_HPP


#include "kernel.hpp"
#include "configs.hpp"
#include "context.hpp"



template <typename T>
class ABM : public kernel<ABM<T>> {

    static_assert(std::is_floating_point_v<T>);

    public:
        ABM(const abm::config<T> &config) : config(config) {}

        auto operator()(const context<T> &ctx) const noexcept {
            const auto drift = config.mu * ctx.dt;
            const auto diffusion = config.sigma * rng::normal(
                ctx.paths, ctx.timesteps, 0.0, std::sqrt(ctx.dt));
            auto ds = (drift + diffusion).eval();
           
            array2d_t<T> states(ctx.paths, ctx.timesteps + 1);
            states << array2d_t<T>::Constant(
                ctx.paths, 1, config.spot), ds;

            cumsum(states);
            return states;
        }

    private:
        const abm::config<T> &config;
};




#endif 
