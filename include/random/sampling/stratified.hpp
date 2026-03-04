#ifndef STRATIFIED_HPP
#define STRATIFIED_HPP


#include "sampler.hpp"


#if defined(__cpp_lib_ranges_enumerate)

/**
 * Clang does not implement std::views::enum as of writing this.
 * Providing a portable alternative is otherwise straightforward,
 * but the objective is also to fully use the stl where possible.
 */

template <typename Uniform>
class StratifiedSampler final : public Sampler {
         
    /**
     * Constructs simple stratified sampler (Hammersley
     * and Morton, 1956) for variance reduction.
     */

    public:
        explicit StratifiedSampler(Uniform uniform) 
            : uniform(std::move(uniform)) {}

        std::vector<f64> sample(u64 n) override {
 
            /**
             * Partitions the distribution support (unit interval) 
             * uniformly and samples once per strata. 
             */           

            const f64 reciprocal = (f64)1.0 / 
                static_cast<f64>(n); 

            auto samples = uniform.sample(n);
            for (auto& [i, sample] : std::views::enumerate(samples))
                sample = (i + sample) * reciprocal;

            return samples;
        }
    
    private:

        /**
         * Copies or multiple-construction of distributions is
         * usually cheap. 
        */

        Uniform uniform;
};
#endif 


#endif 
