#ifndef SIMULATORS_HPP
#define SIMULATORS_HPP



#include "utilities.hpp"



template <typename Class>
class Simulator<Class> {

    public:
        template <typename... Args>
        auto simulate(Args&&... args) {
            return std::move(std::forward<Args>(args)...); 
        }
    
};


#endif

