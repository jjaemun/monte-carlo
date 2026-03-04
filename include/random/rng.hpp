#ifndef RNG_HPP
#define RNG_HPP

#include <utility>

#include "types.hpp"


template <typename EntropySource>
class RandomBitGenerator {
    
    /**
     * Satisfies the (C++11) Uniform Random Bit Generator concept. It 
     * is designed to tie together a local interface for custom random
     * engines downstream, but that is not in scope curently.
     */

    public:
        using result_type = typename EntropySource::result_type;

    public:
        template <typename... Args>
        explicit RandomBitGenerator(Args&&... args) 
            : src(std::forward<Args>(args)...) {}

        auto operator()(void) noexcept {
            return src();
        }
        
        template <typename Iterator>
        void generate(Iterator begin, Iterator end) noexcept {
            for (auto it = begin; it != end; ++it)
                *it = src();
        }

        void seed(u64 seed) noexcept {
            src.seed(seed);
        }

        static constexpr auto min() noexcept { return EntropySource::min(); }
        static constexpr auto max() noexcept { return EntropySource::max(); }

    private:
        EntropySource src;
};


#endif 
