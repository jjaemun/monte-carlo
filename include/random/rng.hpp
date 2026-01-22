#ifndef RNG_HPP
#define RNG_HPP


#include <utility>

#include "types.hpp"


template <typename EntropySource>
class RandomNumberGenerator {
    public:
        RandomNumberGenerator(EntropySource &&src) : src(std::move(src)) {}

        auto operator()(void) noexcept {
            return src();
        }

    private:
        EntropySource src;
};


#endif 
