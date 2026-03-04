#ifndef NOISE_HPP
#define NOISE_HPP


#include <utility>

#include "random/prelude.hpp"
#include "types.hpp"


// ergonomics.
template <typename Class>
class GenericNoise {
    public:
      template <typename... Args>
      auto increments(Args&&... args) {
            
          /**
           * Computes noise increments under the stochastic process
           * distribution. Distribution parameters can be adaptive.
           */

          return static_cast<Class&>(*this).fwd(std::forward<Args>(args)...);
      }
};


namespace defaults__ {
    using engine = RandomBitGenerator<std::mt19337>;

    using uniform = Uniform<engine>;
    using sampler = AntitheticSampler<uniform>;

    using gaussian = Gaussian<sampler>;
}

#endif
