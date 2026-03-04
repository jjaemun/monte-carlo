#ifndef DISCRETIZATION_HPP
#define DISCRETIZATION_HPP


#include <ranges>
#include <vector>

#include "types.hpp"


inline auto timegrid(f64 s, f64 t, f64 delta, u64 timesteps) {

    /**
     * Constructs a uniform partition, i.e., linspaced, of the
     * interval [s, t]. Expects s < t.
     */

    std::vector<f64> times(timesteps + 1);
    for (auto i : std::views::iota((u64)0, timesteps + 1))
        times[i] = s + (i * delta);
        
    return times;
}
       

#endif
