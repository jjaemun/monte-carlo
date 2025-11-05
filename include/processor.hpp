#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP


#include "transforms.hpp"

template <typename Class>
class Processor {

    public:
        Processor(Transform<Class> encoder) : encoder(encoder) {}

        template <typename T>
        auto encode(T&& e) const {
            return encoder.transform(std::forward<T>(e));
        }

        template <typename T>
        auto decode(T&& e) const {
            return encoder.inverse_transform(std::forward<T>(e));
        }

    private:
        Transform<Class> encoder;
};


#endif
