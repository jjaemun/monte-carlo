#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <ranges>
#include <vector>

#include "types.hpp"


class Context final {

    /**
     * Implements simulation context. Timesteps represents the number
     * of intervals, so that we actually have tsteps + 1 observations.
     */

    public:
        Context(u64 timesteps, u64 paths) 
            : timesteps(timesteps), paths(paths) {}
                
        std::vector<f64> timegrid(f64 s, f64 t) const noexcept {

            /**
             * Constructs a uniform partition, i.e., linspaced, of the
             * interval [s, t]. Expects s < t.
             */

            const auto delta = (t - s) / 
                static_cast<f64>(timesteps);
        
            std::vector<f64> times(timesteps + 1);
            for (auto i : std::views::iota((u64)0, timesteps + 1)) {
                times[i] = s + (i * delta);
            }
        
            return times;
        } 
    
        u64 timesteps, paths;
}; 
        

#endif
