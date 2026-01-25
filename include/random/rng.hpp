#ifndef RNG_HPP
#define RNG_HPP


#include <utility>

#include "types.hpp"


template <typename EntropySource>
class RandomNumberGenerator {
    public:
        using result_type = typename EntropySource::result_type;

    public:
        explicit RandomNumberGenerator(EntropySource &&src) 
            : src(std::move(src)) {}

        auto operator()(void) noexcept {
            return src();
        }

        static constexpr auto min() { return EntropySource::min(); }
        static constexpr auto max() { return EntropySource::max(); }

    private:
        EntropySource src;
};


#endif 
