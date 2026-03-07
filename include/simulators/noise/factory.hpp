#ifndef NOISE_FACTORY_HPP
#define NOISE_FACTORY_HPP


#include <random>
#include <ranges>

#include "random/prelude.hpp"
#include "utilities.hpp"


[[nodiscard]]
inline auto make_gaussian(u64 seed) {
        
    /**
     * Creates a standard (centered, unit) gaussian distribution
     * object. 
     */
        
    default__::engine eng(seed);
    default__::uniform uform(eng, 0.0, 1.0);
    default__::sampler smp(uform);

    return default__::gaussian(smp, 0.0, 1.0);
}


[[nodiscard]]
inline auto make_gaussians(u64 threads, u64 seed) {

    /**
     * Threading-ready factory counterpart.
     */

    std::vector<Ret<decltype(make_gaussian), u64>> gaussians{};
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

    default__::engine eng(seed);
    default__::uniform uform(eng, 0.0, 1.0);

    return default__::poisson(uform, lambda);
}


[[nodiscard]]
inline auto make_poissons(u64 threads, u64 seed, f64 lambda) {

    /**
     * Threading-ready factory counterpart.
     */

    std::vector<Ret<decltype(make_poisson), u64, f64>> poissons{};
    poissons.reserve(threads);

    for (auto i : std::views::iota((u64)0, threads))
         poissons.emplace_back(make_poisson(seed + i, lambda));

    return poissons;
}
    


#endif
