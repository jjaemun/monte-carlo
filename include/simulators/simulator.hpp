#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP


#include <ranges>

#include "types.hpp"


class Context final {
    public:
        std::vector<f64> times; 

    public:
        Context(u64 timesteps, u64 paths, f64 s, f64 t) :
            timesteps(timesteps), paths(paths), s(s), t(t) {
                const auto delta = (t - s) / 
                    static_cast<f64>(timesteps);
        
                times.resize(timesteps);
                for (auto i : std::views::iota((u64)0, timesteps)) {
                    times[i] = s + (i * delta);
                } 
            } 
    
        u64 timesteps, paths;
        f64 s, t;
}; 
        

class Simulator {
    public:
        virtual ~Simulator(void) = default;
        virtual std::vector<std::vector<f64>> simulate(const Context &ctx) const = 0;
};


#endif
