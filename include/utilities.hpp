#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <utility>


template <typename... Types>
constexpr auto pack_size = sizeof...(Types);

template <typename f, typename... Args>
using Ret = decltype(std::declval<f>()(std::declval<Args>()...));


#endif 
