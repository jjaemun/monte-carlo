#ifndef TRANSFORMS_IMPLEMENTATION_HPP 
#define TRANSFORMS_IMPLEMENTATION_HPP


#include <Eigen/Core>

#include "tform.hpp"


template <typename Class>
class Operator : public Transform<Class> {

    public:
        


template <typename T>
class Shift : {

    public:
        Shift(T a) : a(a) {}

        auto forward(Eigen::Array<T>&& M) const {
            return M + a;
        }

        auto decode(Eigen::Array<T>&& M) const {
            return M - a;
        }

    private:
        T a;
};


template <typename T>
class Scale


#endif
