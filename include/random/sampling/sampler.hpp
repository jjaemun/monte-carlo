#ifndef SAMPLER_HPP
#define SAMPLER_HPP


#include "random/distribution.hpp"


class Sampler {
    public: 
        virtual ~Sampler(void) = default;
        virtual std::vector<f64> sample(u64 n) = 0;
};


#endif 
