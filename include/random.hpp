#ifndef RANDOM_HPP
#define RANDOM_HPP


#include "types.hpp"


namespace random {
    template <typename T>
    inline auto poisson(index_t n, index_t m, const double lambda) -> ARRAY2D<T> {
        return Eigen::Rand::poisson<ARRAY2D<T>>(
            n, m, detail::default::rng, lambda);
    }

    template <typename T>
    inline auto normal(index_t n, index_t m, T mu, T sigma)  -> ARRAY2D<T> {
        return mu + sigma * Eigen::Rand::normal<ARRAY2D<T>>(
            n, m, detail::default::rng); 
    }

    template <typename T>
    inline auto normal(index_t n, index_t m)  -> ARRAY2D<T> {
        return Eigen::Rand::normal<ARRAY2D<T>>(
            n, m, detail::default::rng); 
    }

}


#endif
