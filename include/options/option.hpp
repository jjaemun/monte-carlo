#ifndef OPTION_HPP
#define OPTION_HPP


#include <vector>
#include <numeric>

#include "types.hpp"


enum class option_type {
    call = 1,
    put = -1
};


class Option {
    public:
        virtual ~Option(void) = default;
        virtual f64 payoff(const std::vector<std::vector<f64>> &process) const noexcept = 0;
};

#endif 
