#ifndef NOISE_FACTORY_HPP
#define NOISE_FACTORY_HPP


#include <random>
#include <ranges>

#include "random/prelude.hpp"


[[nodiscard]]
inline auto make_uniform(u64 seed) {
        
    /**
     * Creates a standard (continuous) uniform distribution
     * object. 
     */
        
    defaults::engine eng(seed);
    
    return defaults::uniform(eng, 0.0, 1.0);
}


[[nodiscard]]
inline auto make_uniforms(u64 threads, u64 seed) {

    /**
     * Threading-ready factory counterpart.
     */

    std::vector<defaults::uniform> uniforms{};
    uniforms.reserve(threads);

    for (auto i : std::views::iota((u64)0, threads))
         uniforms.emplace_back(make_uniform(seed + i));

    return uniforms;
}


[[nodiscard]]
inline auto make_gaussian(u64 seed) {
        
    /**
     * Creates a standard (centered, unit) gaussian distribution
     * object. 
     */
        
    defaults::engine eng(seed);
    defaults::uniform uform(eng, 0.0, 1.0);
    defaults::sampler smp(uform);

    return defaults::gaussian(smp, 0.0, 1.0);
}


[[nodiscard]]
inline auto make_gaussians(u64 threads, u64 seed) {

    /**
     * Threading-ready factory counterpart.
     */

    std::vector<defaults::gaussian> gaussians{};
    gaussians.reserve(threads);

    for (auto i : std::views::iota((u64)0, threads))
         gaussians.emplace_back(make_gaussian(seed + i));

    return gaussians;
}


[[nodiscard]]
inline auto make_poisson(u64 seed, f64 lambda) {

    /**
     * Creates a poisson distribution object with intensity
     * lambda. 
     */

    defaults::engine eng(seed);
    defaults::uniform uform(eng, 0.0, 1.0);

    return defaults::poisson(uform, lambda);
}


[[nodiscard]]
inline auto make_poissons(u64 threads, u64 seed, f64 lambda) {

    /**
     * Threading-ready factory counterpart.
     */

    std::vector<defaults::poisson> poissons{};
    poissons.reserve(threads);

    for (auto i : std::views::iota((u64)0, threads))
         poissons.emplace_back(make_poisson(seed + i, lambda));

    return poissons;
}
    


#endif
