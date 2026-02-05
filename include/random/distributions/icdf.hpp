#ifndef ICDF_HPP 
#define ICDF_HPP 

#include <cmath>
#include <limits>
#include <numbers>
#include <ranges>
#include <vector>

#include "types.hpp"


class InverseCumulativeDistribution {
    public:
        virtual ~InverseCumulativeDistribution() = default;
        virtual f64 operator()(const f64 n) const = 0;
};

class GaussianInverseCumulativeWichura : public InverseCumulativeDistribution {
    
    /* ALGO. AS241 APPL. STATIST. (1988) VOL.37, NO 3 */

    public: 
        f64 operator()(const f64 u) const override {
            const auto split1 = (f64)0.425e0; 
            const auto split2 = (f64)5.0e0; 

            const auto ONE = (f64)1.0;
            const auto const1 = (f64)0.180625e0; 
            const auto const2 = (f64)1.6e0;


            // coeffs. for u close to 1/2.
            const auto A0 = (f64)3.3871328727963666080e0;
            const auto A1 = (f64)1.3314166789178437745e2;
            const auto A2 = (f64)1.9715909503065514427e3;
            const auto A3 = (f64)1.3731693765509461125e4;
            const auto A4 = (f64)4.5921953931549871457e4;
            const auto A5 = (f64)6.7265770927008700853e4;
            const auto A6 = (f64)3.3430575583588128105e4;
            const auto A7 = (f64)2.5090809287301226727e3;
            const auto B1 = (f64)4.2313330701600911252e1;
            const auto B2 = (f64)6.8718700749205790830e2;
            const auto B3 = (f64)5.3941960214247511077e3;
            const auto B4 = (f64)2.1213794301586595867e4;
            const auto B5 = (f64)3.9307895800092710610e4;
            const auto B6 = (f64)2.8729085735721942674e4;
            const auto B7 = (f64)5.2264952788528545610e3;

            // coeffs. for u neither close to 1/2 nor 0 or 1.
            const auto C0 = (f64)1.42343711074968357734e0;
            const auto C1 = (f64)4.63033784615654529590e0;
            const auto C2 = (f64)5.76949722146069140550e0;
            const auto C3 = (f64)3.64784832476320460504e0;
            const auto C4 = (f64)1.27045825245236838258e0;
            const auto C5 = (f64)2.41780725177450611770e-1;
            const auto C6 = (f64)2.27238449892691845833e-2;
            const auto C7 = (f64)7.74545014278341407640e-4;
            const auto D1 = (f64)2.05319162663775882187e0;
            const auto D2 = (f64)1.67638483018380384940e0;
            const auto D3 = (f64)6.89767334985100004550e-1;
            const auto D4 = (f64)1.48103976427480074590e-1;
            const auto D5 = (f64)1.51986665636164571966e-2;
            const auto D6 = (f64)5.47593808499534494600e-4;
            const auto D7 = (f64)1.05075007164441684324e-9;

            // coeffs. for u very near 0 or 1
            const auto E0 = (f64)6.65790464350110377720e0;
            const auto E1 = (f64)5.46378491116411436990e0;
            const auto E2 = (f64)1.78482653991729133580e0;
            const auto E3 = (f64)2.96560571828504891230e-1;
            const auto E4 = (f64)2.65321895265761230930e-2;
            const auto E5 = (f64)1.24266094738807843860e-3;
            const auto E6 = (f64)2.71155556874348757815e-5;
            const auto E7 = (f64)2.01033439929228813265e-7;
            const auto F1 = (f64)5.99832206555887937690e-1;
            const auto F2 = (f64)1.36929880922735805310e-1;
            const auto F3 = (f64)1.48753612908506148525e-2;
            const auto F4 = (f64)7.86869131145613259100e-4;
            const auto F5 = (f64)1.84631831751005468180e-5;
            const auto F6 = (f64)1.42151175831644588870e-7;
            const auto F7 = (f64)2.04426310338993978564e-15;

            if (u <= (f64)0.0) 
                return -std::numeric_limits<f64>::infinity();

            if (u >= (f64)1.0)
                return std::numeric_limits<f64>::infinity();

            const auto Q = u - (f64)(1.0 / 2.0);
            if (std::abs(Q) <= split1) {
                const f64 R = const1 - Q * Q;
    
                auto num = A7; 
                num = std::fma(num, R, A6);
                num = std::fma(num, R, A5);
                num = std::fma(num, R, A4);
                num = std::fma(num, R, A3);
                num = std::fma(num, R, A2);
                num = std::fma(num, R, A1);
                num = std::fma(num, R, A0);

                auto denom = B7;
                denom = std::fma(denom, R, B6);
                denom = std::fma(denom, R, B5);
                denom = std::fma(denom, R, B4);
                denom = std::fma(denom, R, B3);
                denom = std::fma(denom, R, B2);
                denom = std::fma(denom, R, B1);
                denom = std::fma(denom, R, ONE);
                
                return Q * num / denom;
            }

            else {
                f64 R{};
                if (Q < 0.0)
                    R = std::sqrt(-std::log(u));
                else 
                    R = std::sqrt(-std::log((f64)1.0 - u));

                f64 ret{};
                if (R < split2) {
                    R -= const2;
    
                    auto num = C7; 
                    num = std::fma(num, R, C6);
                    num = std::fma(num, R, C5);
                    num = std::fma(num, R, C4);
                    num = std::fma(num, R, C3);
                    num = std::fma(num, R, C2);
                    num = std::fma(num, R, C1);
                    num = std::fma(num, R, C0);

                    auto denom = D7;
                    denom = std::fma(denom, R, D6);
                    denom = std::fma(denom, R, D5);
                    denom = std::fma(denom, R, D4);
                    denom = std::fma(denom, R, D3);
                    denom = std::fma(denom, R, D2);
                    denom = std::fma(denom, R, D1);
                    denom = std::fma(denom, R, ONE);
                     
                    ret = num / denom; 
                }

                else {
                    R -= split2;
     
                    auto num = E7; 
                    num = std::fma(num, R, E6);
                    num = std::fma(num, R, E5);
                    num = std::fma(num, R, E4);
                    num = std::fma(num, R, E3);
                    num = std::fma(num, R, E2);
                    num = std::fma(num, R, E1);
                    num = std::fma(num, R, E0);

                    auto denom = F7;
                    denom = std::fma(denom, R, F6);
                    denom = std::fma(denom, R, F5);
                    denom = std::fma(denom, R, F4);
                    denom = std::fma(denom, R, F3);
                    denom = std::fma(denom, R, F2);
                    denom = std::fma(denom, R, F1);
                    denom = std::fma(denom, R, ONE);
                    
                    ret = num / denom;
            }
            
            if (Q < (f64)0.0)
                return -ret;

            return ret;
        }
    }
};

#endif
