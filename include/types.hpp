#ifndef TYPES_HPP
#define TYPES_HPP

#include <EigenRand/EigenRand>
#include <Eigen/Dense>



namespace rng {
    using vmt64_t = Eigen::Rand::Vmt19937_64;
}

namespace detail {
    namespace defaults {
        auto rngen = rng::vmt64_t{ 0xff };
    }
}


//!public aliases / types.
using index_t = Eigen::Index;

template <typename Type>
using array1d_t = Eigen::Array<Type, Eigen::Dynamic, 1>;

template <typename Type>
using array2d_t = Eigen::Array<Type, Eigen::Dynamic, Eigen::Dynamic>;


#endif
