#ifndef ARITHMETIC_BROWNIAN_MOTION_HPP
#define ARITHMETIC_BROWNIAN_MOTION_HPP


#include <cmath>

#include "configs.hpp"
#include "simulator.hpp"
#include "types.hpp"



template <typename T>
class ArithmeticBrownianMotion : public Simulator<ArithmeticBrownianMotion<T>> {

    static_assert(std::is_floating_point_v<T>);
    
    ARRAY2D<T> samples;

    public:
        ArithmeticBrownianMotion(INDEX timesteps, INDEX paths) : timesteps(timesteps), paths(paths) {
            samples = RANDOM_NORMAL_GEN<ARRAY2D<T>>(
                paths, timesteps, DEFAULT_RNG); 
        }

        auto sim(const abm::config<T> &config, const T s, const T t) -> ARRAY2D<T> {
            T dt = (t - s) / T(timesteps);
             
            auto drift = ARRAY2D<T>::Constant(paths, timesteps, config.mu * dt);
            auto diffusion = config.sigma * samples * std::sqrt(dt);

            auto ds = drift + diffusion;
           
            ARRAY2D<T> s(paths, timesteps + 1);
            s.col(0) = ARRAY2D<T>::Constant(paths, 1, config.spot);
            s.block(0, 1, paths, timesteps) = 
                s.col(0).rowwise() + ds.rowwise().cumsum();

            return s;
        }

    
    private:
        INDEX timesteps, paths;
};




#endif 
