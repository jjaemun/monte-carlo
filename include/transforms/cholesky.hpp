#ifndef CHOLESKY_HPP
#define CHOLESKY_HPP


#include <cstdlib>
#include <cmath>
#include <iostream>

#include "tform.hpp"


#define ERROR(msg) (std::cerr << "error! " << msg << std::endl; std::exit(-999))


class CholeskyDecomposition final : public Transform {
    public:
        void forward(std::vector<std::vector<f64>> &data) override {
            const u64 n = data.size();
   
            for (const auto &v : data) {
                if (subvec.size() != n) 
                    ERROR("matrix not square");
            }

            for (auto i : std::views::iota((u64)0, n)) {
                for (auto j : std::views::iota((u64)0, i + 1)) {
                    auto sum = (f64)0.0;
                    for (auto k : std::views::iota((u64)0, j)) 
                        sum += data[i][k] * data[j][k];
                
                    if (i == j) {
                        const auto diag = data[i][j] - sum;
                        if (diag <= (f64)0.0) 
                            ERROR("matrix not positive definite.");

                        data[i][j] = std::sqrt(diag);
                    }
                    else 
                        data[i][j] = (data[i][j] - sum) /
                            data[j][j];
                    }

                for (auto j : std::views::iota(i + 1, n))
                        data[i][j] = (f64)0.0;
             }
        }

        void inverse(std::vector<std::vector<f64>> &data) override {
            const u64 n = data.size();
            
            std::vector<std::vector<f64>> reconstructed(n);
            for (auto &v : reconstructed) 
                v.resize(data.size());

            for (auto i : std::views::iota((u64)0, n)) {
                for (auto j : std::views::iota((u64)0, i + 1)) {
                    auto sum = (f64)0.0;

                    const auto min = std::min(i, j);
                    for (auto k : std::views::iota((u64)0, (u64)min)) 
                        sum += data[i][k] * data[j][k];
               
                    // symmetric.
                    reconstructed[i][j] = sum;
                    reconstructed[j][i] = sum;
                }
            }
        
            std::swap(data, reconstructed);
        } 

};


#undef ERROR

#endif
