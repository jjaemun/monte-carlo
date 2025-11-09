#ifndef CONFIGS_HPP 
#define CONFIGS_HPP 


namespace abm {
    template <typename T>
    struct config {
        T spot;
        T mu;
        T sigma;
    };
}


namespace gbm {
    template <typename T>
    struct config {
        T spot;
        T mu;
        T sigma;
    };
}

namespace ou {
    template <typename T>
    struct config {
        T spot;
        T kappa;
        T theta;
        T sigma;
    };
}


#endif
