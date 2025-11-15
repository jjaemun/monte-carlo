#ifndef ORNSTEIN_UHLENBECK_HPP
#define ORNSTEIN_UHLENBECK_HPP


#include "kernel.hpp"
#include "configs.hpp"
#include "context.hpp"



template <typename T>
class OU : public kernel<OU> {
    
    static_assert(std::is_floating_point_v<T>);

    public:
        OU(const ou::config<T> &config) : config(config) {}

        auto operator()(const context<T> &ctx) const noexcept {
            array2d_t<T> states(ctx.paths, ctx.timesteps) <<
                array2d_t<T>::Constant(ctx.paths, 1, config.spot);

            const auto sdev = config.sigma * std::sqrt(
                1.0 - std::exp(-2.0 * config.kappa * ctx.dt)
                    / (2.0 * config.kappa));
            const auto rvs = rng::normal(ctx.paths, 
                ctx.timesteps - 1, 0.0, stdev);

            for (index_t i = 1; i < ctx.timesteps; ++i) {
                states.col(i) = config.theta + (states.col(i - 1)
                    - config.theta) * std::exp(-config.kappa * ctx.dt) 
                        + rvs.col(i - 1);
            }

            return states;
        }

    private:
        const ou::config<T> &config;

        
#endif 
