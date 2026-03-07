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
        virtual void forward(std::vector<std::vector<f64>> &data) = 0;
        virtual void inverse(std::vector<std::vector<f64>> &data) = 0;
};


template <typename... Transforms>
class Composite final : public Transform {

    /**
     * Composite transform for multiprocesses. Transformations 
     * are assumed to be bijective, i.e., the inverse mapping 
     * exists and is well defined such that 

     *              Tform.inverse(Tfomr.forward(·))

     * forms an identity function for each Tform in the pipeline. 
     * They are not assumed to be commutative, hence we traverse
     * the pipeline in reverse when applying such inverses.
     */
    
    static_assert((std::is_base_of_v<Transform, Transforms> && ...));

    public:
        explicit Composite(Transforms*... transforms) 
            : transforms{ std::unique_ptr<Transform>(transforms)... } {}

        void forward(std::vector<std::vector<f64>> &data) override {
            for (auto &tform : transforms) {
                tform->forward(data);
            }
        }

        void inverse(std::vector<std::vector<f64>> &data) override {
            for (auto &tform : transforms | std::views::reverse) {
                 tform->inverse(data);
            }
        }

    private:
        std::vector<std::unique_ptr<Transform>> transforms;
};


#endif
