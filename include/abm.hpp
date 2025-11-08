#ifndef ARITHMETIC_BROWNIAN_MOTION_HPP
#define ARITHMETIC_BROWNIAN_MOTION_HPP


#include <EigenRand/EigenRand>
#include <Eigen/Dense>

#include <cassert>
#include <cmath>

#include "simulator.hpp"


template <typename T>
class ArithmeticBrownianMotion : Simulator<ArithmeticBrownianMotion<T>> {
    
    template <typename Type>
    using NDARRAY = Eigen::ArrayXX<Type>;

    using INDEX = Eigen::Index;

    
    public:
        ArithmeticBrownianMotion(T spot, T mu, T sigma, INDEX timesteps, INDEX paths) 
         : spot(spot), mu(mu), sigma(sigma), timesteps(timesteps), paths(paths) {}

        template <typename RNG>
        auto sim(const T s, const T t, RNG rng) -> NDARRAY<T> {
            assert(s < t);

            T dt = (t - s) / T(timesteps);
            NDARRAY<T> dw = Eigen::Rand::normal<NDARRAY<T>>(
                paths, timesteps, rng) * std::sqrt(dt); 
             
            NDARRAY<T> drift = NDARRAY<T>::Constant(paths, timesteps, mu * dt);
            NDARRAY<T> diffusion = sigma * dw;

            NDARRAY ds = drift + diffusion;
           
            NDARRAY<T> s(paths, timesteps + 1);
            s.col(0) = NDARRAY<T>::Constant(paths, 1, spot);
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
