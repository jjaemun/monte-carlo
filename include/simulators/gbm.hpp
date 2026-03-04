#ifndef GEOMETRIC_BROWNIAN_MOTION_HPP
#define GEOMETRIC_BROWNIAN_MOTION_HPP

#include <cmath>
#include <utility>

#include "noise/brownian.hpp"
#include "simulator.hpp"


class GeometricBrownianMotion : public Simulator {

    /**
     * Simulates paths of geometric Brownian motion under the physical
     * measure. Uses exact discretization. Noise is accordingly Brownian.
     */

    BrownianProcess brownian;

    public:
        explicit GeometricBrownianMotion(u64 timesteps, u64 paths, f64 spot, f64 mu, f64 sigma) 
                : timesteps(timesteps), paths(paths), spot(spot), mu(mu), sigma(sigma) {}

        std::vector<std::vector<f64>> simulate(f64 s, f64 t) override {
            const auto timedelta = (t - s) / 
                static_cast<f64>(timesteps);

            const auto drift = timedelta * 
                (mu - (f64)0.5 * sigma * sigma);

            std::vector<std::vector<f64>> process(timesteps + 1);
            for (auto &timestep : process)
                timestep.resize(paths);

            // fill spot.
            std::ranges::fill(process.front(), spot);

            for (auto i : std::views::iota((u64)1, timesteps + 1)) {
                const auto diffusions = brownian.increments(paths, timedelta);

                for (auto [current, previous, diffusion] : std::views::zip(process[i], process[i - 1], diffusions)) 
                    current = std::exp(drift + sigma * diffusion) 
                        * previous;
                
            }

            return process;
        } 

    private:
        u64 timesteps, paths;
        f64 spot, mu, sigma;
};


#endif 
