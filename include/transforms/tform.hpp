#ifndef TFORM_HPP
#define TFORM_HPP

#include <ranges>
#include <type_traits>
#include <vector>

#include "types.hpp"


class Transform {
    public:
        virtual void transform(std::vector<f64> &data) = 0;
        virtual void inverse_transform(std::vector<f64> &data) = 0;

        virtual ~Transform() = default;
};


template <typename... Transforms>
class Composite final : public Transform {
    
    static_assert((std::is_base_of_v<Transform, Transforms> && ...);

    public:
        explicit Composite(Transforms*... transforms) : transforms{ transforms... } {}

        void transform(std::vector<f64> &data) override {
            for (auto &tform : transforms) {
                tform->transform(data);
            }
        }

        void inverse_transform(std::vector<f64> &data) override {
            for (auto &tform : transforms | std::views::reverse) {
                 tform->inverse_transform(data);
            }
        }

    private:
        std::vector<Transform*> transforms;
};


#endif
