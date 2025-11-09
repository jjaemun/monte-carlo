#ifndef TYPES_HPP
#define TYPES_HPP

#include <EigenRand/EigenRand>
#include <Eigen/Dense>


namespace detail {
    namespace default {
        auto rng = random::rng::vmt64_t{ 0xff };

    }
}

namespace random {
    namespace rng {
        using vmt64_t = Eigen::Rand::Vmt19937_64;
    }
}


//!public aliases / types.
using index_t = Eigen::Index;
using dynamic_t = Eigen::Dynamic;

template <typename Type>
using array1d_t = Eigen::Array<Type, dynamic_t, index_t(1)>;

template <typename Type>
using array2d_t = Eigen::Array<Type, dynamic_t, dynamic_t>;


#endif
