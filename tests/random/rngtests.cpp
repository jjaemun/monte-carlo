#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <ranges>
#include <vector>

#include "random/rng.hpp"


namespace default {
    static const u64 seed = 0xff;
} // namespace default.


TEST(rngtest, TrivialRandomGeneration) {
    
    /* @test TrivialRandomGeneration: trivially checks random
            number yields from rng class. */

    RandomNumberGenerator rng(std::mt19937{default::seed});

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
