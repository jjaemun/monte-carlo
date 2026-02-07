#ifndef KERNEL_HPP
#define KERNEL_HPP


#include <utility>


template <typename functor>
class kernel {

    template <typename... Args>
    using Ret = decltype(std::declval<functor>()(std::declval<Args>()...));

    public:
        template <typename... Args> __attribute__((always_inline))
        constexpr auto evaluate(Args&&... args) const noexcept -> Ret<Args...> {
            return static_cast<functor>(*this)(std::forward<Args>(args)...); 
        }
};


#endif
