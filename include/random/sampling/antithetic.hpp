#ifndef ANTITHETIC_HPP
#define ANTITHETIC_HPP


#include "sampler.hpp"


class AntitheticSampler final : public Sampler {
         
    /**
     * Constructs pairwise antithetic coupling (Hammersley and Morton, 1956), 
     * under standard uniform distribution. 
     */

    public:
        explicit AntitheticSampler(UniformDistribution *distribution) 
            : distribution(distribution) {}

        std::vector<f64> sample(u64 n) override {
 
            /**
             * Standard marginal uniformity is trivially satisfied in the 
             * one-dimensional case. 
             */           
            
            std::vector<f64> antithetics{};
            antithetics.reserve(n);

            const u64 half = n / (u64)2; 

            const auto samples = distribution->sample(half);
            for (const auto &sample : samples) {
                antithetics.push_back(sample);
                antithetics.push_back((f64)1.0 - sample);
            }

            if (n & 1) 
                antithetics.push_back(dist->sample(1).front());

            return antithetics;
        }
    
    private:

       /**
        * Copies and multiple-construction of distributions are usually 
        * cheap, in opposite to random engines, which should be initialised 
        * once per thread (~~rarely also synchronized across them). 
        */ 

        UniformDistribution *distribution;
};

#endif 
