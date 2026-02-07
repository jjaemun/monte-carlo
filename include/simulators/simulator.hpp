#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP


#include <ranges>

#include "context.hpp"
#include "types.hpp"


class Simulator {
    public:
        virtual ~Simulator(void) = default;
        virtual std::vector<std::vector<f64>> simulate(const Context &ctx) const = 0;
};


#endif
