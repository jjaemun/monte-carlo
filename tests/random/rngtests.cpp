#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <ranges>
#include <vector>

#include "random/rng.hpp"


namespace detail {
    static constexpr u64 seed = 0xff;
} // namespace detail.


TEST(rngtest, TrivialNonDegenerateSequence) {
    
    /* @test TrivialNonDegenerateSequence: trivially checks rng class
            as a non-degenerate source of entropy. */

    RandomNumberGenerator rng(std::mt19937{detail::seed});

    std::vector<u64> samples((u64)1e4);
    for (auto &sample : samples) {
         sample = rng();
    }

    bool cmpeq = std::all_of(
        samples.begin(), samples.end(), [&] (u64 v) {
            return v == samples.front();
        });

    ASSERT_FALSE(cmpeq);
}


TEST(rngtest, TrivialDeterministicallyReproducibleSequence) {
        
    /* @test TrivialDeterministically...: checks behavior is preserved
           accross rng objects sharing a same seed. */

    RandomNumberGenerator rng1(std::mt19937{detail::seed});
    RandomNumberGenerator rng2(std::mt19937{detail::seed});

    bool cmpeq = true;
    for (auto i : std::views::iota(0, 1e4)) {
          cmpeq &= (rng1() == rng2());
    }

    ASSERT_TRUE(cmpeq);
}


TEST(rngtest, TrivialSeedDependentSequence) {
         
    /* @test TrivialSeedDependentSequence: trivially checks different 
            seeds yield different sequences. */

    RandomNumberGenerator rng1(std::mt19937{detail::seed});
    RandomNumberGenerator rng2(std::mt19937{detail::seed + 1});

    bool cmpeq = false;
    for (auto i : std::views::iota(0, 1e4)) {
        if (rng1() == rng2()) {
            cmpeq = true;
            break;
        }
    }

    ASSERT_FALSE(cmpeq);
}

