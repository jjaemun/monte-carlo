#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP


#include <type_traits>

#include "utilities.hpp"


template <typename Class>
class Simulator {
    
    static_assert(std::is_base_of_v<Simulator<Class>, Class>);
    
    public:
        template <typename... Args>
        auto simulate(Args&&... args) {
            return down_cast<Class>(*this).sim(std::forward<Args>(args)...); 
        }
};


#endif
