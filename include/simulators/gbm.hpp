#ifndef GEOMETRIC_BROWNIAN_MOTION_HPP
#define GEOMETRIC_BROWNIAN_MOTION_HPP


#include "random/gaussian.hpp"
#include "simulator.hpp"


template <typename RandomNumberGenerator>
class GeometricBrownianMotion : Simulator {
        
        RandomNumberGenerator rng;

    public:
        GeometricBrownianMotion(f64 spot, f64 mu, f64 sigma, RandomNumberGenerator& rng) :
            spot(spot), mu(mu), sigma(sigma), rng(rng) {}

        std::vector<std::vector<f64>> simulate(const Context &ctx) const override {} 

    private:
        f64 spot, mu, sigma;
};


#endif 
