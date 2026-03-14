#pragma once


#include <expected>
#include <utility>


template <typename... Types>
constexpr auto pack_size = sizeof...(Types);

  /**
   * Returns the length of variadic pack. 
  */


template <typename Err>
[[nodiscard]] auto unex(Err e) noexcept {
    
    /**
     * Constructs std::unexpected from submodule error.
    */

    return std::unexpected(std::move(e));
}


template <typename f, typename... Args>
using Ret = decltype(std::declval<f>()(std::declval<Args>()...));

  /**
   * Infers return type given a callable and input 
   * argument types.
  */
