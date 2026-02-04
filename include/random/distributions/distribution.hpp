#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP

#include <ranges>
#include <utility>
#include <vector>

#include "types.hpp"


class StatisticalDistribution {
    public:
        virtual ~StatisticalDistribution() = default;
        virtual std::vector<f64> sample(u64 n) = 0;
};


#endif
