#ifndef TRANSFORMS_HPP
#define TRANSFORMS_HPP


#include "meta.hpp"

template <typename Class>
class Transform {

    static_assert(std::is_base_of<Transform<Class>, Class>);

    public:
    
        template <typename... Args>
        auto transform(Args&&... args) const {
            return down_cast<Class>(*this).forward(std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto inverse_transform(Args&&... args) const {
            return down_cast<Class>(*this).backward(std::forward<Args>(args)...);
        }
};


template <typename... Transforms>
class Composite : public Transform<Composite<Transforms...>> {

    static_assert(pack_size<Transforms...> > 1);

    public:
        Composite(Transforms&&... tforms) : tforms(std::move(tforms)...) {}

        template <typename... Args>
        auto forward(Args&&... args) const {
            auto tffmap = [&](auto&... tfs) const {
                return (..., tfs.forward(std::forward<Args>(args)...));
            };

            return std::apply(tffmap, tforms);
        }

        template <typename... Args>
        auto backward(Args&&... args) const {
            auto tfbmap = [&](auto&... tfs) const {
                return (..., tfs.forward(std::forward<Args>(args)...));
            }; 
    
            return std::apply(tfbmap, reversed(tforms));
        }
    
    
    private:
        std::tuple<Transforms...> tforms;


#endif
