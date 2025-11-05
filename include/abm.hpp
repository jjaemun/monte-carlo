#ifndef ARITHMETIC_BROWNIAN_MOTION_HPP
#define ARITHMETIC_BROWNIAN_MOTION_HPP



#include <Eigen/Dense>

#include "simulator.hpp"


template <typename T>
class ArithmeticBrownianMotion : public Simulator<ArithmeticBrownianMotion> {
    
    public:
        ArithmeticBrownianMotion(T mu, T sigma, T spot, std::size_t timesteps, std::size_t paths)
         : mu(mu), sigma(sigma), spot(spot), timesteps(timesteps), paths(paths) {}

        auto sim(double s, double t) -> Eigen::Array<T>* {
            

    private:

};



#endif
