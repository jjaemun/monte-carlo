#ifndef KERNEL_HPP
#define KERNEL_HPP


#include <cmath>

#include "algorithm.hpp"
#include "utilities.hpp"
#include "random.hpp"


template <typename functor>
class kernel {

    template <typename... Args>
    using Ret = decltype(std::declval<functor>()(std::declval<Args>()...));

    public:
        template <typename... Args>
        auto simulate(Args&&... args) const -> Ret<Args...> {
            return down_cast<functor>(*this)(std::forward<Args>(args)...); 
        }
};


#endif
