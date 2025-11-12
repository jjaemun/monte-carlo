#ifndef SIMULATION_CONTEXTS_HPP
#define SIMULATION_CONTEXTS_HPP


#include "types.hpp"


template <typename T>
class context {
    
    static_assert(std::is_floating_point_v<T>);

    public:

        context(index_t timesteps, index_t paths, T s, T t) : 
            timesteps(timesteps), paths(paths), s(s), t(t) {
                tm = array1d_t<T>::LinSpaced(
                    timesteps, 0.0, 1.0);

        }

        array1d_t<T> tm;

        index_t timesteps;
        index_t paths;

        T s;
        T t;
};


#endif
