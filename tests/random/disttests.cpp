#include <gtest/gtest.h>

#include <random>
#include <ranges>
#include <vector>

#include "random/rng.hpp"
#include "random/gaussian.hpp"
#include "random/poisson.hpp"

#include "stats/empirical.hpp"
#include "stats/gaussian.hpp"
#include "stats/poisson.hpp"


namespace detail {
    static constexpr u64 seed = 0xff;
    static constexpr u64 ssize = (u64)2e6;
    static constexpr f64 tol = (f64)1e-2;
} // namespace detail.


template <typename TestDistribution, typename TheoreticMoments>
void test(TestDistribution *dist, TheoreticMoments&& theoretic) {
    SampleDistributionMoments empirical{};
    auto samples = dist->sample(detail::ssize);

    ASSERT_NEAR(
        empirical.mean(samples), 
        theoretic.mean(*dist), 
        detail::tol
    );
    ASSERT_NEAR(
        empirical.variance(samples), 
        theoretic.variance(*dist), 
        detail::tol
    );
    ASSERT_NEAR(
        empirical.skewness(samples), 
        theoretic.skewness(*dist), 
        detail::tol
    );
    ASSERT_NEAR(
        empirical.kurtosis(samples), 
        theoretic.kurtosis(*dist), 
        detail::tol
    );
}

TEST(disttest, StatisticalMomentsCorrectness) {

    /* @test Satatistical...: checkes whether drawn samples converge
            to distribution theoretical moments. */

    RandomNumberGenerator rng{ std::mt19937(detail::seed) };

    Gaussian gaussian {rng, 0.0, 1.0};
    Poisson poisson{rng, 2.0};

    test(&gaussian, GaussianMoments{}); 
    test(&poisson, PoissonMoments{}); 
}

