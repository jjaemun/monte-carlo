#ifndef STATS_HPP
#define STATS_HPP


#include <type_traits>

#include "utilities.hpp"


template<typename Class>
class TheoreticMoments {
    
    static_assert(std::is_base_of_v<TheoreticMoments<Class>, Class>);

    public:
      template <typename... Args>
        auto mean(Args&&... args) {

            /**
             * Computes theoretic path of one-time first order 
             * moments over the simulation period.
             */

            return down_cast<Class>(*this).fm(std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto variance(Args&&... args) {

            /**
             * Returns theoretic dispersion / second-order one-
             * time central moments over the simulation period.
             */

            return down_cast<Class>(*this).scm(std::forward<Args>(args)...);
        } 

        template <typename... Args>
        auto autocovariance(Args&&... args) {

            /**
             * Computes the two-times (mixed) second-order 
             * process central moments.
             */

            return down_cast<Class>(*this).mscm(std::forward<Args>(args)...);
        } 
};       

template<typename Class>
class SampleMoments {
    
    static_assert(std::is_base_of_v<SampleMoments<Class>, Class>);

    public:
      template <typename... Args>
        auto mean(Args&&... args) {

            /**
             * Computes empirical process mean from pathwise
             * realisations over simulation period.
             */

            return down_cast<Class>(*this).sm(std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto variance(Args&&... args) {

            /**
             * Returns empirical variance from pathwise 
             * realisations over the simulation period.
             */

            return down_cast<Class>(*this).sv(std::forward<Args>(args)...);
        } 

        template <typename... Args>
        auto autocovariance(Args&&... args) {

            /**
             * Computes the two-times empirical covariance from 
             * from process pathwise realisations.
             */

            return down_cast<Class>(*this).sc(std::forward<Args>(args)...);
        } 
};      


#endif
