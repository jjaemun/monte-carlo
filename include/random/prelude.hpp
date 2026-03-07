#ifndef RANDOM_PRELUDE_HPP
#define RANDOM_PRELUDE_HPP

#include <random>

#include "rng.hpp"

#include "projections/prelude.hpp"
#include "sampling/prelude.hpp"
#include "distributions/prelude.hpp"


namespace default__ {
    using engine   = RandomBitGenerator<std::mt19937>;
    using uniform  = Uniform<engine>;
    using sampler  = AntitheticSampler<uniform>;
    using gaussian = Gaussian<sampler>;
    using poisson  = PoissonKnuth<uniform>;
}

#endif
