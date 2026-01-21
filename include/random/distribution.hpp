#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP

#include <ranges>
#include <utility>
#include <vector>

#include "types.hpp"


class StatisticalDistribution {
    public:
        virtual ~StatisticalDistribution() = default;
        virtual auto sample(u64 n) = 0;
};

#endif
