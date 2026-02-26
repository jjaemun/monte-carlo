#ifndef BLOCK_HPP
#define BLOCK_HPP


#include <array>
#include <span>

#include "types.hpp"
#include "utilities.hpp"


#define constant__ inline constexpr u64


constant__ BLOCK_SIZE = 2048;


template <typename T, u64 N = count_from_bytes<T>(BLOCK_SIZE)>
class Block {
    public:
        auto begin() noexcept { return buffer.begin(); }
        auto end() noexcept { return buffer.end(); }

        auto begin() const noexcept { return buffer.begin(); }
        auto end() const noexcept { return buffer.end(); }

        T &operator[](u64 i) noexcept { return buffer[i]; }
        const T &operator[](u64 i) const noexcept { return buffer[i]; }

        T *data() noexcept { return buffer.data(); }
        const T *data() const noexcept { return buffer.data(); }

    private:
        std::array<T, N> buffer;
};


#undef constant__

#endif
