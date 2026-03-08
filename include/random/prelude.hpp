#ifndef RANDOM_PRELUDE_HPP
#define RANDOM_PRELUDE_HPP

#include <random>

#include "rng.hpp"

#include "projections/prelude.hpp"
#include "sampling/prelude.hpp"
#include "distributions/prelude.hpp"


namespace defaults {
    
    /**
     * ergonomics! ideally, a centralised api with the available
     * features provides benchmarke-optimal configurations for 
     * each isolated organ in the random number generation layer.
     */

    using engine   = RandomBitGenerator<std::mt19937>;
    using uniform  = Uniform<engine>;
    using sampler  = AntitheticSampler<uniform>;
    using gaussian = Gaussian<sampler>;
    using poisson  = PoissonKnuth<uniform>;

} // namespace defaults.

#endif
