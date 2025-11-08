#ifndef ARITHMETIC_BROWNIAN_MOTION_HPP
#define ARITHMETIC_BROWNIAN_MOTION_HPP


#include <EigenRand/EigenRand>
#include <Eigen/Dense>

#include <cassert>
#include <cmath>

#include "simulator.hpp"


template <typename T>
class ArithmeticBrownianMotion : Simulator<ArithmeticBrownianMotion<T>> {

    template <Class>
    using RANDOM_NORMAL_ARRAY = Eigen::Rand::normal<Class>;
    
    template <typename Type>
    using NDARRAY = Eigen::ArrayXX<Type>;

    using INDEX = Eigen::Index;

    
    public:
        ArithmeticBrownianMotion(T spot, T mu, T sigma, INDEX timesteps, INDEX paths) 
         : spot(spot), mu(mu), sigma(sigma), timesteps(timesteps), paths(paths) {}

        template <typename Rng>
        auto sim(const T s, const T t, Rng rng) -> NDARRAY<T> {
            assert(s < t);

            T dt = (t - s) / T(timesteps);
            auto dw = RANDOM_NORMAL_ARRAY<NDARRAY<T>>(paths, timesteps, rng) 
                * std::sqrt(dt); 
             
            T drift = mu * dt;
            auto diffusion = sigma * dw;

            auto ds = drift + diffusion;
            ds.col(0) = NDARRAY<T>::Constant(paths, 1, spot);
            
            return ds.rowwise().cumsum(1);
    }
         

    private:
        T spot, mu, sigma;
        INDEX timesteps;
        INDEX paths;
};


#endif 
