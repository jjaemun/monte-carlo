#ifndef SIMULATION_CONTEXTS_HPP
#define SIMULATION_CONTEXTS_HPP


#include "types.hpp"
#include "random.hpp"


namespace diffusion {
    template <typename T>
    class context {
        
        static_assert(std::is_floating_point_v<T>);

        public:
            context(INDEX timesteps, INDEX paths) : 
                timesteps(timesteps), paths(paths) {
                    ss = RANDOM_NORMAL_GEN<ARRAY2D<T>>(
                        paths, timesteps, DEFAULT_RNG);
                    tm = ARRAY1D<T>::LinSpaced(
                        timesteps, 0.0, 1.0);

            }

            ARRAY2D<T> ss;
            ARRAY2D<T> tm;

            INDEX timesteps;
            INDEX paths;
}; 


#endif
