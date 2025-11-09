#ifndef TYPES_HPP
#define TYPES_HPP

#include <EigenRand/EigenRand>
#include <Eigen/Dense>


using index_t = Eigen::Index;
using dynamic_t = Eigen::Dynamic;

template <typename Type>
using ARRAY1D = Eigen::Array<Type, dynamic_t, index_t(1)>;

template <typename Type>
using ARRAY2D = Eigen::Array<Type, dynamic_t, dynamic_t>;


namespace random {
    namespace rng {
        using mt64_t = Eigen::Rand::Vmt19937_64;
    }
}

namespace detail {
    namespace default {
        // default seed for reproducibility;
        int seed = 0xff;
    
        // generic engine. Support is limited currently.
        auto rng = random::rng::mt64_t{ seed };

        //
    }
}


#endif
