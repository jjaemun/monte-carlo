#ifndef ARITHMETIC_BROWNIAN_MOTION_HPP
#define ARITHMETIC_BROWNIAN_MOTION_HPP


#include <cmath>

#include "simulator.hpp"
#include "runtime.hpp"


template <typename T>
class ArithmeticBrownianMotion : public Simulator<ArithmeticBrownianMotion<T>> {

    static_assert(std::is_floating_point_v<T>);

    public:
        template <typename RNG>
        ArithmeticBrownianMotion(T spot, T mu, T sigma, INDEX timesteps, INDEX paths); 

        auto sim(const T s, const T t) -> ARRAY2D<T> {
            T dt = (t - s) / T(timesteps);
             
            auto drift = ARRAY2D<T>::Constant(paths, timesteps, mu * dt);
            auto diffusion = sigma * samples * std::sqrt(dt);

            auto ds = drift + diffusion;
           
            ARRAY2D<T> s(paths, timesteps + 1);
            s.col(0) = ARRAY2D<T>::Constant(paths, 1, spot);
            s.block(0, 1, paths, timesteps) = 
                s.col(0).rowwise() + ds.rowwise().cumsum();

            return s;
        }

        T spot, mu, sigma;
    
    private:
        ARRAY2D<T> samples;
        INDEX timesteps, paths;
};


template <typename T>
ArithmeticBrownianMotion<T>::ArithmeticBrownianMotion(T spot, T mu, T sigma, INDEX timesteps, INDEX paths)
: spot(spot), mu(mu), sigma(sigma), timesteps(timesteps), paths(paths) {
    this->samples = RANDOM_NORMAL_GEN<ARRAY2D<T>(
        paths, timesteps, DEFAULT_RNG);
}





#endif 
