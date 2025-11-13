#ifndef RANDOM_HPP
#define RANDOM_HPP


#include "types.hpp"


namespace rng {
    template <typename T>
    inline auto normal(index_t n, index_t m, T mu, T sigma) noexcept {
        return mu + sigma * Eigen::Rand::normal<array2d_t<T>>(
            n, m, detail::defaults::rngen); 
    }

    template <typename T>
    inline auto normal(index_t n, index_t m) noexcept {
        return Eigen::Rand::normal<array2d_t<T>>(
            n, m, detail::defaults::rngen); 
    }

    template <typename T>
    inline auto normal(index_t n, T mu, T sigma) noexcept {
        return mu + sigma * Eigen::Rand::normal<array1d_t<T>>(
            n, detail::defaults::rngen); 
    }

    template <typename T>
    inline auto normal(index_t n) noexcept {
        return Eigen::Rand::normal<array1d_t<T>>(
            n, detail::defaults::rngen); 
    }

    template <typename T>
    inline auto poisson(index_t n, index_t m, T lambda) noexcept {
        return Eigen::Rand::poisson<array2d_t<T>>(
            n, m, detail::defaults::rngen, lambda);
    }

    template <typename T>
    inline auto poisson(index_t n, T lambda) noexcept {
        return Eigen::Rand::poisson<array1d_t<T>>(
            n, detail::defaults::rngen, lambda);
    }
}


#endif
