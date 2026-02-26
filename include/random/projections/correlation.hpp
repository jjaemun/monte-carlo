#ifndef CORRELATION_HPP
#define CORRELATION_HPP

#include <cstdlib>
#include <ranges>
#include <iostream>

#include "transforms/cholesky.hpp"
#include "projection.hpp"


#define ERROR(msg) (std::cerr << "error! " << msg << std::endl; std::exit(-999))


class CorrelatedGaussians final : public Projection {

    /**
     * Computes the linear correlation of Gaussian row vectors, given the target
     * covariance matrix. It is a structure endowing transform.
     */

    private:
 
        /**
         * Intuitively, the factorization by means of Cholesky decomposition 
         * is a multidimensional generalization of affine correlation used for
         * scalars. This time, from the covariance definition, we find the 
         * lower triangular matrix solving the linear system. The result follows 
         * directly from the closure of gaussians under linear combinations. 
         */

       CholeskyDecomposition cholesky;

    public: 
        explicit 
        CorrelatedGaussians(std::vector<std::vector<f64>> covariance)
            : factors(std::move(covariance)) {
                cholesky.forward(factors);
        }
        
        void project(std::vector<std::vector<f64>> &gaussians) const override {
            // samples per gaussian row vec.
            const auto dims = 
                static_cast<u64>(gaussians.front().size());

            for (const auto& gaussian : gaussians)
                if (gaussian.size() != dims)
                    ERROR("dimension mismatch");

            std::vector<f64> correlated(dims);
            for (auto &gaussian : gaussians) {
                for (auto i : std::views::iota((u64)0, dims)) {
                    auto sum = (f64)0.0;
                    for (auto j : std::views::iota((u64)0, i + 1)) 
                        sum += factors[i][j] * gaussian[j];

                    correlated[i] = sum;
                }
                std::swap(gaussian, correlated);
            }
        }

    private:
        std::vector<std::vector<f64>> factors;
};


#undef ERROR


#endif
