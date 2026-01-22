#ifndef TFORM_HPP
#define TFORM_HPP


#include <memory>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>

#include "types.hpp"


class Transform {
    public:
        virtual ~Transform() = default;
        virtual void forward(std::vector<f64> &data) = 0;
        virtual void inverse(std::vector<f64> &data) = 0;
};


template <typename... Transforms>
class Composite final : public Transform {
    
    static_assert((std::is_base_of_v<Transform, Transforms> && ...));

    public:
        explicit Composite(std::unique_ptr<Transforms>... transforms) 
            : transforms{ std::move(transforms)... } {}

        void forward(std::vector<f64> &data) override {
            for (auto &tform : transforms) {
                tform->forward(data);
            }
        }

        void inverse(std::vector<f64> &data) override {
            for (auto &tform : transforms | std::views::reverse) {
                 tform->inverse(data);
            }
        }

    private:
        std::vector<std::unique_ptr<Transform>> transforms;
};


#endif
