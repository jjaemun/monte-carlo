#ifndef ARITHMETIC_BROWNIAN_MOTION_HPP
#define ARITHMETIC_BROWNIAN_MOTION_HPP


#include <cassert>
#include <cmath>

#include "simulator.hpp"
#include "runtime.hpp"


template <typename T>
class ArithmeticBrownianMotion : public Simulator<ArithmeticBrownianMotion<T>> {
    
    public:
        ArithmeticBrownianMotion(T spot, T mu, T sigma, INDEX timesteps, INDEX paths) 
         : spot(spot), mu(mu), sigma(sigma), timesteps(timesteps), paths(paths) {}

        template <typename RNG>
        auto sim(const T s, const T t, RNG &&rng) -> ARRAY2D<T> {
            assert(s < t);

            T dt = (t - s) / T(timesteps);
            auto dw = Eigen::Rand::normal<ARRAY2D<T>>(
                paths, timesteps, rng) * std::sqrt(dt); 
             
            auto drift = ARRAY2D<T>::Constant(paths, timesteps, mu * dt);
            auto diffusion = sigma * dw;

            auto ds = drift + diffusion;
           
            ARRAY2D<T> s(paths, timesteps + 1);
            s.col(0) = ARRAY1D<T>::Constant(paths, spot);
            s.block(0, 1, paths, timesteps) = 
                s.col(0).rowwise() + ds.rowwise().cumsum();

            return S;
    }
         

    private:
        T spot, mu, sigma;
        INDEX timesteps;
        INDEX paths;
};


#endif 
