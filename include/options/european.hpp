#ifndef EUROPEAN_OPTION_HPP
#define EUROPEAN_OPTION_HPP


#include <cmath>

#include "option.hpp"



class EuropeanOption : public Option {
    public:
        EuropeanOption(f64 strike, f64 tenor, option_type type) 
            : strike(strike), tenor(tenor), type(type) {}
            
        f64 payoff(const std::vector<std::vector<f64>> &process) const noexcept override {
            // european options use ending period underlying prices.
            const auto &prices = process.back();

            auto sum = (f64)0.0;
            for (const auto &price : prices) {
                const auto intrinsic = (price - strike) 
                    * static_cast<f64>(type);
            
                sum += std::max((f64)0.0, intrinsic); 
            }
            
            return sum / static_cast<f64>(prices.size());   
        }

    private:
        f64 strike, tenor;
        option_type type;
};

#endif 
