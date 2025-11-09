#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <EigenRand/EigenRand>
#include <Eigen/Dense>


using INDEX = Eigen::Index;


using DYNAMIC = Eigen::Dynamic;


template <typename Type>
using ARRAY1D = Eigen::Array<Type, DYNAMIC, INDEX(1)>;


template <typename Type>
using ARRAY2D = Eigen::Array<Type, DYNAMIC, DYNAMIC>;


template <typename Class>
using RANDOM_NORMAL_GEN = Eigen::Rand::NormalGen<Class>;


using DEFAULT_RNG = Eigen::Rand::Vmt19937_64; 


#endif
