#ifndef UTILITIES_HPP
#define UTILITIES_HPP


#include <utility>


template <typename... Types>
constexpr auto pack_size = sizeof...(Types);


#endif 
