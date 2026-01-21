#ifndef RNG_HPP
#define RNG_HPP


#include <utility>

#include "types.hpp"


template <typename Class>
class RandomNumberGenerator {
    public:
        RandomNumberGenerator(const Class &rng) : rng(std::move(rng)) {}

        auto operator()(void) noexcept {
            return rng();
        }

    private:
        Class rng;
};


#endif 
