#ifndef BASE_TRANSFORMS_HPP
#define BASE_TRANSFORMS_HPP


#include <type_traits>

#include "algorithm.hpp"


template <typename Class>
class Transform {

    static_assert(std::is_base_of_v<Transform<Class>, Class>);

    public:
    
        template <typename T>
        auto transform(T&& e) const {
            return down_cast<Class>(*this).forward(std::forward<T>(e));
        }

        template <typename T>
        auto inverse_transform(T&& e) const {
            return down_cast<Class>(*this).backward(std::forward<T>(e));
        }
};


template <typename... Transforms>
class Composite : public Transform<Composite<Transforms...>> {

    static_assert(pack_size<Transforms...> > 1);

    public:
        Composite(Transforms&&... tforms) : tforms(std::move(tforms)...) {}

        template <typename T>
        auto forward(T&& e) const {
            auto image = std::forward<T>(e);
            auto tfmap = [&](const auto&... tfs) {
                return ((image = tfs.forward(image)), ...);
            };

            std::apply(tfmap, tforms);
            return image;
        }

        template <typename T>
        auto backward(T&& e) const {
            auto preimage = std::forward<T>(e);
            auto tfmap = [&](const auto&... tfs) {
                return ((preimage = tfs.backward(preimage)), ...);
            };

            std::apply(tfmap, reverse(tforms));
            return preimage;
        }
    
    private:
        std::tuple<Transforms...> tforms;
};


#endif
