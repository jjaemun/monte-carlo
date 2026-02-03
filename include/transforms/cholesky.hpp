#ifndef CHOLESKY_HPP
#define CHOLESKY_HPP


#include <cstdlib>
#include <cmath>
#include <iostream>

#include "tform.hpp"


#define ERROR(msg) (std::cerr << "error! " << msg << std::endl)


class CholeskyDecomposition final : public Transform {
    public:
        void forward(std::vector<std::vector<f64>> &data) override {
            const u64 n = data.size();
    
            std::for_each(data.begin(), data.end(), [&](const auto &subvec) {
                    if (subvec.size() != n) {
                        ERROR("matrix not square");
                        std::exit(-999);
                    }
                }
            );

            for (auto i : std::views::iota((u64)0, n)) {
                for (auto j : std::views::iota((u64)0, i + 1)) {
                    auto sum = (f64)0.0;
                    for (auto k : std::views::iota((u64)0, j)) 
                        sum += data[i][k] * data[j][k];
                
                    if (i == j) {
                        const auto diag = data[i][j] - sum;
                        if (diag <= (f64)0.0) {
                            ERROR("matrix not positive definite.");
                            std::exit(-999);
                        }
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

    private:
};


#undef ERROR

#endif
