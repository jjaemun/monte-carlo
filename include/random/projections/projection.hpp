#ifndef PROJECTION_HPP
#define PROJECTION_HPP


#include <ranges>
#include <vector>

#include "types.hpp"


class Projection {
    public:
        virtual ~Projection(void) = default;
        virtual void project(std::vector<std::vector<f64>> &data) const = 0;
};


#endif
