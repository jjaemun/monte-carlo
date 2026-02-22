#ifndef RNG_HPP
#define RNG_HPP

#include <utility>

#include "types.hpp"


template <typename EntropySource>
class RandomBitGenerator {
    public:
        using result_type = typename EntropySource::result_type;

    public:
        template <typename... Args>
        explicit RandomBitGenerator(Args&&... args) 
            : src(std::forward<Args>(args)...) {}

        auto operator()(void) noexcept {
            return src();
        }

        static constexpr auto min() noexcept { return EntropySource::min(); }
        static constexpr auto max() noexcept { return EntropySource::max(); }

    private:
        EntropySource src;
};


#endif 
