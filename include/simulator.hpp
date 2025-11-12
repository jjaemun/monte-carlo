#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP


#include <cmath>

#include "utilities.hpp"
#include "random.hpp"


template <typename kernel>
class Simulator {

    template <typename... Args>
    using Ret = decltype(std::declval<kernel>()(std::declval<Args>()...));

    public:
        template <typename... Args>
        auto simulate(Args&&... args) const -> Ret<Args...> {
            return down_cast<kernel>(*this)(std::forward<Args>(args)...); 
        }
};


#endif
