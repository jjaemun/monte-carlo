#ifndef OPTION_HPP
#define OPTION_HPP


#include <span>
#include <numeric>

#include "types.hpp"


enum class option_type {
    call = 1,
    put = -1
};


class Option {
    public:
        virtual ~Option(void) = default;
        virtual payoff(std::vector<std::vector<f64>> &process) const noexcept = 0;
};

#endif 
