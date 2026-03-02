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

#include "random/sampling/antithetic.hpp"

#include "stats/empirical.hpp"
#include "stats/gaussian.hpp"
#include "stats/poisson.hpp"


namespace detail {
    static constexpr u64 seed = (u64)0xff;
    static constexpr u64 ssize = (u64)2e6;
    static constexpr f64 tol = (f64)1e-2;
} // namespace detail.


template <typename Distribution, typename TheoreticMoments>
void test(Distribution dist, TheoreticMoments&& theoretic) {
    SampleDistributionMoments empirical{};
    auto samples = dist.sample(detail::ssize);
        
    for (auto i = 0; i < 11; ++i) {
        std::cout << samples[i];
    }
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
    
    //RandomBitGenerator<std::mt19937> rng(detail::seed);
    Uniform uniform(std::mt19937(detail::seed), 0.0, 1.0);
    AntitheticSampler antithetic(uniform);
     

    Gaussian gaussian {antithetic, 0.0, 1.0};
    //Poisson poisson{rng, 2.0};

    test(gaussian, GaussianMoments{}); 
    //test(&poisson, PoissonMoments{}); 
}

