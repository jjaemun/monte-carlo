#ifndef SIMULATION_DRIVER_HPP
#define SIMULATION_DRIVER_HPP

#include <memory>
#include <type_traits>
#include <vector>

#include "simulators/simulator.hpp"
#include "utilities.hpp"


struct results_cache__;
 
    /**
     * in development... we need a struct to comunicate with pricing and    
     * plotting layers.
     */


template <typename... Simulators>
class SimulationDriver {
    
    static_assert((std::is_base_of_v<Simulator, Simulators> && ...));

    public:
        SimulationDriver(Simulators*... sims) {
            sims{ std::unique_ptr<Simulator>(sims)... } {}

        void simulate(f64 s, f64 t, results_cache__ *cache) {
            for (const auto &sim : sims) 
                cache.push_back(sim->simulate(s, t);
        }
            
    private:
        std::vector<std::unique_ptr<Simulator>> sims;
};

#endif 
