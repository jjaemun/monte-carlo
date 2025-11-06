#ifndef TRANSFORMS_IMPLEMENTATION_HPP 
#define TRANSFORMS_IMPLEMENTATION_HPP


#include <numbers>
#include <cmath>

#include <Eigen/Core>

#include "tform.hpp"


template <typename T>
class LinearOperator : public Transform<LinearOperator<T>> {

    public:
        LinearOperator(const Eigen::ArrayXX<T> &A) : A(A) {} 
    
        auto forward(Eigen::ArrayXX<T> &e) -> Eigen::ArrayXX<T> {
            return (A.matrix() * e.matrix()).array();
        }

        auto backward(Eigen::ArrayXX<T>& e) const -> Eigen::ArrayXX<T> {
            return A.matrix().fullPivLu().solve(e.matrix()).array();
        }

    private:
        const Eigen::ArrayXX<T> &A;
};

template <typename T>
class AffineOperator : public Transform<AffineOperator<T>> {

    public:
        AffineOperator(const Eigen::ArrayXX<T> &A, const T &b) : A(A), b(b) {}

        auto forward(Eigen::ArrayXX<T> &e) const -> Eigen::ArrayXX<T> {
            return (A.matrix() * e.matrix()).array() + b;
        }

        auto backward(Eigen::ArrayXX<T> &e) const -> Eigen::ArrayXX<T> {
            return A.matrix().fullPivLu().solve((e - b).matrix()).array();
        }

    private:
        const Eigen::ArrayXX<T> &A;
        T b;
};

template <typename T>
class BoxMuller : public Transform<BoxMuller<T>> {

    public:

        auto forward(Eigen::ArrayXX<T> &e) const -> Eigen::ArrayXX<T> {
            const auto mid = e.cols() / 2;

            auto ulhs = e.leftCols(mid);
            auto urhs = e.rightCols(mid);

            Eigen::ArrayXX<T> gaussiansamples(e.rows(), e.cols());

            auto zlhs = gaussiansamples.leftCols(mid);
            auto zrhs = gaussiansamples.rightCols(mid);

            const Eigen::ArrayXX<T> factor = sqrt(-2.0 * log(ulhs));
            const Eigen::ArrayXX<T> theta = 2.0 * std::numbers::pi_v<T> * urhs;
            
            zlhs = factor * cos(theta);
            zrhs = factor * sin(theta);

            return gaussiansamples; 
        }

        auto backward(Eigen::ArrayXX<T> &e) const -> Eigen::ArrayXX<T> {
            const auto mid = e.cols() / 2;

            auto zlhs = e.leftCols(mid);
            auto zrhs = e.rightCols(mid);

            const Eigen::ArrayXX<T> factor = square(zlhs) + square(zrhs);
            
            Eigen::ArrayXX<T> uniformsamples(e.rows(), e.cols());

            uniformsamples.leftCols(mid) = exp(-0.5 * factor);
            for (Eigen::Index i = 0; i < e.rows(); ++i) {
                for (Eigen::Index j = 0; j < mid; ++j) {
                    T theta = std::atan2(zrhs(i, j), zlhs(i, j));
                    if (theta < T(0))
                        theta += T(2 * std::numbers::pi_v<T>);
                    
                    uniformsamples(i, mid + j) = theta / 
                        T(2 * std::numbers::pi_v<T>);
                }
            }

            return uniformsamples;
        }
};
                   

#endif
