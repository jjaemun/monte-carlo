#ifndef TRANSFORMS_IMPLEMENTATION_HPP 
#define TRANSFORMS_IMPLEMENTATION_HPP


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
        Eigen::ArrayXX<T> &A;
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
        Eigen::ArrayXX<T> &A;
        T b;
};

template <typename T>
class BoxMuller : public Transform<BoxMuller<T>> {

    public:

        auto forward(Eigen::ArrayXX<T> &e) const -> Eigen::ArrayXX<T> {
            const auto mid = e.cols() / 2;

            auto ulhs = e.leftCols(mid);
            auto urhs = e.rightCols(mid);

            Eigen::ArrayXX<T> z(e.rows(), e.cols());

            auto zlhs = z.leftCols(mid);
            auto zrhs = z.rightCols(mid);

            const Eigen::ArrayXX<T> factor = sqrt(-2.0 * log(ulhs));
            const Eigen::ArrayXX<T> theta = 2.0 * M_PI * urhs;
            
            zlhs = factor * cos(theta);
            rhs = factor * sin(theta);

            return z; 
        }


#endif
