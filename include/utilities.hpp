#ifndef UTILITIES_HPP 
#define UTILITIES_HPP


#include <utility>


template <typename T>
class down_cast;


template<typename To>
class down_cast<To> {
    
    public:
        template <typename From>
        constexpr auto operator()(From &from) -> To& {
            return static_cast<To&>(from);
        }
};


template<typename To>
class down_cast<const To> {
    
    public:
        template<typename From>
        constexpr auto operator()(const From &from) const -> const To& {
            return static_cast<const To&>(from);
        }
};


#endif
