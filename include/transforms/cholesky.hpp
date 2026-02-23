#ifndef CHOLESKY_HPP
#define CHOLESKY_HPP


#include <cstdlib>
#include <cmath>
#include <iostream>

#include "tform.hpp"


#define ERROR(msg) (std::cerr << "error! " << msg << std::endl; std::exit(-999))


class CholeskyDecomposition final : public Transform {
    
    /**
     * (Thm. 23.1 (Trefethen & Bau, 1997)) Every hemitian positive definite 
     * matrix has a unique Cholesky factorization. 
     */

    public:
        void forward(std::vector<std::vector<f64>> &data) override {
            const u64 n = data.size();

            if (n == 0)
                ERROR("matrix empty.");
    
            for (const auto &subvec : data) {
                if (subvec.size() != n) 
                    ERROR("matrix not square.");
            }

            std::vector<std::vector<f64>> decomp(n);
            for (auto &subvec : decomp) 
                subvec.resize(data.size());

            for (auto j : std::views::iota((u64)0, n)) {
                auto sum = (f64)0.0;
                
                // diagonal elems.
                for (auto k : std::views::iota((u64)0, j)) 
                    sum += decomp[j][k] * decomp[j][k];
                
                const auto diag = data[j][j] - sum;
                if (diag <= (f64)0.0) 
                    ERROR("matrix not positive definite.");

                decomp[j][j] = std::sqrt(diag);
                   
                // subdiagonal elems.
                for (auto i : std::views::iota(j + 1, n)) {
                    auto sum = (f64)0.0;
                    for (auto k : std::views::iota((u64)0, j))
                        sum += decomp[i][k] * decomp[j][k];
                    
                    decomp[i][j] = (data[i][j] - sum) /
                         data[j][j];
                }
             }
            
            std::swap(data, decomp);
        }

        void inverse(std::vector<std::vector<f64>> &data) override {
            const u64 n = data.size();
            
            std::vector<std::vector<f64>> recomp(n);
            for (auto &v : recomp) 
                v.resize(data.size());

            for (auto i : std::views::iota((u64)0, n)) {
                for (auto j : std::views::iota((u64)0, i + 1)) {
                    const auto min = std::min(i, j);

                    auto sum = (f64)0.0;
                    for (auto k : std::views::iota((u64)0, (u64)min)) 
                        sum += data[i][k] * data[j][k];
               
                    // symmetric.
                    recomp[i][j] = sum;
                    recomp[j][i] = sum;
                }
            }
        
            std::swap(data, recomp);
        } 

};


#undef ERROR

#endif
