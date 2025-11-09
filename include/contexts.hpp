#ifndef SIMULATION_CONTEXTS_HPP
#define SIMULATION_CONTEXTS_HPP


#include "random.hpp"


namespace diffusion {
    template <typename T>
    class context {
        
        static_assert(std::is_floating_point_v<T>);

        public:
            context(index_t timesteps, index_t paths) : 
                timesteps(timesteps), paths(paths) {
                    tm = ARRAY1D<T>::LinSpaced(
                        timesteps, 0.0, 1.0);

            }

            auto nn(T mu, T sigma) const noexcept -> ARRAY2D<T> {
                return random::normal<ARRAY2D<T>>(
                    paths, timesteps, mu, sigma);
            }

            ARRAY1D<T> tm;

            index_t timesteps;
            index_t paths;
    };
}


namespace jump {
    template <typename T>
    class context {
        
        static_assert(std::is_floating_point_v<T>);

        public:
            context(index_t timesteps, index_t paths) : 
                timesteps(timesteps), paths(paths) {
                    tm = ARRAY1D<T>::LinSpaced(
                        timesteps, 0.0, 1.0);

            }

            auto pp(T intensity) const noexcept -> ARRAY2D<T> {
                return random::poisson(
                    paths, timesteps, intensity);
            }

            ARRAY1D<T> tm;

            index_t timesteps;
            index_t paths;
    };
}


#endif
