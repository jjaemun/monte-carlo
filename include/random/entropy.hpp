#ifndef ENTROPY_HPP
#define ENTROPY_HPP


template <typename Class>
class EntropySource {
   
    /*
     * Represents the canonical probability space. As such
     * we simply endow it with a random engine, to handle 
     * each distribution at the random variable level.
    */

    public:
        EntropySource(const Class &src) : src(std::move(src) {}

        auto get_src(void) const -> &Class { 
            return &src; 
        }
    
    private:
        Class src;
};


#endif 
