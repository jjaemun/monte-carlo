#ifndef SIMULATORS_HPP
#define SIMULATORS_HPP



#include "utilities.hpp"



template <typename Class>
class Simulator<Class> {

    public:
        template <typename... Args>
        auto simulate(Args&&... args) {
            return down_cast<Class>(*this).sim(std::forward<Args>(args)...); 
        }
};


#endif

