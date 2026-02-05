#ifndef ICDF_HPP 
#define ICDF_HPP 

#include <cmath>
#include <numbers>
#include <ranges>
#include <vector>

#include "types.hpp"


class InverseCumulativeDistribution {
    public:
        virtual ~InverseCumulativeDistribution() = default;
        virtual f64 operator()(const f64 n) const = 0;
};


#endif
