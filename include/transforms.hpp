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
        Eigen::ArrayXX<T> A;
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
        Eigen::ArrayXX<T> A;
        T b;
};




#endif
