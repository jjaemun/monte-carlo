#include <matplot/matplot.h>


#include <vector>
#include <ranges>

#include "simulators/abm.hpp"
#include "stats/empirical.hpp"


int main(void) {
    
    // params.
    constexpr u64 timesteps = 1000;
    constexpr u64 paths = 100;

    constexpr f64 spot = 100.0;
    constexpr f64 mu = 0.05;
    constexpr f64 sigma = 0.150;

    constexpr f64  s = 0.0;
    constexpr f64 t = 1.0;


    ArithmeticBrownianMotion abm(timesteps, paths, spot, mu, sigma);
    const auto process = abm.simulate(s, t);

    // timegrid.
    auto times = timegrid(s, t, timesteps);

    // init figure.
    auto f = matplot::figure(true);
    auto ax = f->current_axes();

    // transpose, plot.
    for (auto path : std::views::iota((u64)0, paths)) {
        std::vector<f64> realization(timesteps + 1);
        for (auto timestep : std::views::iota((u64)0, timesteps + 1))
            realization[timestep] = process[timestep][path];
        
        ax->plot(times, realization)->color({0.7f, 0.7f, 0.7f}).line_width(0.5);
        ax->hold(true);
    }

    ax->xlabel("t");
    ax->ylabel("S(t)");
    ax->title("Arithmetic Brownian Motion");
    f->show();

    return 0;
}
