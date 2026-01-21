#ifndef RNG_HPP
#define RNG_HPP


template <typename Class>
class RandomNumberGenerator {
    public:
       RandomNumberGenerator(const Class &rng_) : rng(std::move(rng_)) {}

    private:
        Class rng;
};


#endif 
