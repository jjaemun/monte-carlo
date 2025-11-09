#ifndef TYPES_HPP
#define TYPES_HPP

#include <EigenRand/EigenRand>
#include <Eigen/Dense>


using INDEX = Eigen::Index;


using DYNAMIC = Eigen::Dynamic;


template <typename Type>
using ARRAY1D = Eigen::Array<Type, DYNAMIC, INDEX(1)>;


template <typename Type>
using ARRAY2D = Eigen::Array<Type, DYNAMIC, DYNAMIC>;


using DEFAULT_RNG = Eigen::Rand::Vmt19937_64; 


#define RANDOM_NORMAL_GEN Eigen::Random::normal



#endif
