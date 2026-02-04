#ifndef ICDF_HPP 
#define ICDF_HPP 

#include <cmath>
#include <numbers>
#include <ranges>
#include <vector>

#include "types.hpp"


class InverseCumulativeDistributionFunction {
    public:
        virtual ~InverseCumulativeDistributionFunction() = default;
        virtual f64 operator()(const u64 n) const = 0;
};


#endif
