#ifndef RANDOM_HPP
#define RANDOM_HPP


#include "types.hpp"


namespace random {
    template <typename T>
    inline auto normal(index_t n, index_t m, T mu, T sigma) noexcept -> array2d_t<T> {
        return mu + sigma * Eigen::Rand::normal<array2d_t<T>>(
            n, m, detail::default::rng); 
    }

    template <typename T>
    inline auto normal(index_t n, index_t m) noexcept -> array2d_t<T> {
        return Eigen::Rand::normal<array2d_t<T>>(
            n, m, detail::default::rng); 
    }

    template <typename T>
    inline auto poisson(index_t n, index_t m, T lambda) noexcept -> array2d_t<T> {
        return Eigen::Rand::poisson<array2d_t<T>>(
            n, m, detail::default::rng, lambda);
    }

}


#endif
