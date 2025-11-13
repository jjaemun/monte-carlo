#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP


#include "types.hpp"


template <typename Type>
inline void cumsum(Type &array) noexcept {
    for (index_t j = 1; j < array.cols(); ++j) {
        array.col(j) += array.col(j - 1);
    }
}


#endif
