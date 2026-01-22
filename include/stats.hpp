#ifndef STATS_HPP
#define STATS_HPP


#include <cmath>
#include <numeric>
#include <vector>


class GenericTheoreticMoments {
    public:
      template <typename... Args>
        virtual auto mean(Args&&... args) const = 0;

            /**
             * Computes theoretic path of one-time first order 
             * moments over the simulation period.
             */


        template <typename... Args>
        virtual auto variance(Args&&... args) const = 0;

            /**
             * Returns theoretic dispersion / second-order one-
             * time central moments over the simulation period.
             */

        template <typename... Args>
        virtual auto autocovariance(Args&&... args) const = 0;

            /**
             * Computes the two-times (mixed) second-order 
             * process central moments.
             */
};       

class GenericSampleMoments {
    public:
        template <typename... Args>
        virtual auto mean(Args&&... args) const = 0;

            /**
             * Computes empirical process mean from pathwise
             * realisations over simulation period.
             */


        template <typename... Args>
        virtual auto variance(Args&&... args) const = 0;

            /**
             * Returns empirical variance from pathwise 
             * realisations over the simulation period.
             */


        template <typename... Args>
        virtual auto autocovariance(Args&&... args) = 0;

            /**
             * Computes the two-times empirical covariance from 
             * from process pathwise realisations.
             */
};      


#endif
