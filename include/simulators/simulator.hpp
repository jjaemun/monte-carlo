#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP


#include <vector>
#include <ranges>

#include "discretization.hpp"
#include "types.hpp"


class Simulator {
    public:
        virtual ~Simulator(void) = default;
        virtual std::vector<std::vector<f64>> simulate(f64 s, f64 t) = 0;
};


#endif
