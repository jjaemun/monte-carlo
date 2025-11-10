#ifndef SIMULATION_DRIVER_HPP
#define SIMULATION_DRIVER_HPP


#include "context.hpp"


template <typename... Simulators>
class SimulationDriver {
    
    static_assert(pack_size<Simulators...> > 0);

    public:
        SimulationDriver(Simulators&&... sims) {
            sims = { std::make_unique<std::common_type<std::decay_t<Simulators>>...>(
                std::forward<Simulators>(sims))...  };
        }

        void simulate(const context& ctx) {

        }
            

    
    private:
        std::vector<std::unique_ptr<Simulator>> sims;
};

#endif 
