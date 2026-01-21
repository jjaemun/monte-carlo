#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP


#include <utility>

#include "types.hpp"


template <typename Class>
class StatisticalDistribution {
    public:
        virtual ~StatisticalDistribution() = default;
        virtual auto sample(u64 n) = 0;
};

#endif
