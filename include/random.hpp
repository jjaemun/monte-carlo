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
    inline auto normal(index_t n, T mu, T sigma) noexcept -> array1d_t<T> {
        return mu + sigma * Eigen::Rand::normal<array1d_t<T>>(
            n, detail::default::rng); 
    }

    template <typename T>
    inline auto normal(index_t n) noexcept -> array1d_t<T> {
        return Eigen::Rand::normal<array1d_t<T>>(
            n, detail::default::rng); 
    }

    template <typename T>
    inline auto poisson(index_t n, index_t m, T lambda) noexcept -> array2d_t<T> {
        return Eigen::Rand::poisson<array2d_t<T>>(
            n, m, detail::default::rng, lambda);
    }

    template <typename T>
    inline auto poisson(index_t n, T lambda) noexcept -> array1d_t<T> {
        return Eigen::Rand::poisson<array1d_t<T>>(
            n, m, detail::default::rng, lambda);
    }
}


#endif
