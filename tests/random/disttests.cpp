#include <gtest/gtest.h>

#include <iostream>
#include <random>
#include <ranges>
#include <vector>

#include "random/rng.hpp"

#include "random/distributions/exponential.hpp"
#include "random/distributions/gaussian.hpp"
#include "random/distributions/poisson.hpp"
#include "random/distributions/uniform.hpp"

#include "stats/empirical.hpp"
#include "stats/theoretic.hpp"


namespace detail {
    static constexpr u64 seed = (u64)0xff;
    static constexpr u64 ssize = (u64)2e6;
    static constexpr f64 tol = (f64)5e-2;
} // namespace detail.


template <typename Distribution, typename TheoreticMoments>
void test(Distribution dist, TheoreticMoments&& theoretic) {
    SampleDistributionMoments empirical{};
    auto samples = dist.sample(detail::ssize);

    ASSERT_NEAR(
        empirical.mean(samples), 
        theoretic.mean(dist), 
        detail::tol
    );

    ASSERT_NEAR(
        empirical.variance(samples), 
        theoretic.variance(dist), 
        detail::tol
    );

    ASSERT_NEAR(
        empirical.skewness(samples), 
        theoretic.skewness(dist), 
        detail::tol
    );

    ASSERT_NEAR(
        empirical.kurtosis(samples), 
        theoretic.kurtosis(dist), 
        detail::tol
    );
}

TEST(disttest, StatisticalMomentsCorrectness) {

    /* @test Satatistical...: checkes whether drawn samples converge
            to distribution theoretical moments. */
    
    RandomBitGenerator<std::mt19937> rng(detail::seed);

    Uniform uniform(rng, 0.0, 1.0);
    Exponential exponential{uniform, 2.0};
    Gaussian gaussian {uniform, 0.0, 1.0};
    PoissonKnuth poisson {uniform, 2.0};

    test(uniform, UniformMoments{}); 
    test(gaussian, GaussianMoments{}); 
    test(poisson, PoissonMoments{}); 
    test(exponential, ExponentialMoments{}); 
}

