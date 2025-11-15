#ifndef FELLER_SQUARE_ROOT_HPP
#define FELLER_SQUARE_ROOT_HPP

#include "kernel.hpp"
#include "configs.hpp"
#include "context.hpp"


template <typename T>
class FELL : public kernel<FELL<T>> {

    static_assert(std::is_floating_point_v<T>);

    public:
        FELL(const feller::config<T> &config) : config(config) {}

        auto operator()(context<T> &ctx) const noexcept {
            array2d_t<T> states(ctx.paths, ctx.timesteps) <<
                array2d_t<T>::Constant(ctx.paths, 1, config.spot);

            const auto rvs = rng::normal(ctx.paths, ctx.timesteps - 1);
            const auto A = ((config.sigma * config.sigma) 
                / config.kappa) * (std::exp(-config.kappa * ctx.dt) 
                    - std::exp(-2.0 * config.kappa * ctx.dt));
            const auto B = config.theta * (config.sigma * config.sigma)
                / (2.0 * config.kappa) * std::pow((1.0 - std::exp(-config.kappa
                    * ctx.dt)), 2);
            
            for (index_t i = 1; i < ctx.timesteps; ++i) {
                states.col(i) = (config.theta * (states.col(i - 1) - config.theta)
                    * std::exp(-config.theta * ctx.dt) + sqrt(A * states.col(i - 1)
                        + B) * rvs.col(i - 1)).max((T) 0.0);
            }

            return states;
        }

    private:
        const feller::config<T> &config;

};




#endif
