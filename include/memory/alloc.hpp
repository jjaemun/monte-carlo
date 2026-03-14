#pragma once


#include <array>
#include <expected>

#include "block.hpp"


enum class allocation_error {
    overwrite,
    overflow,
    invalid_free,
};


template <u64 size, u64 alignment__ = alignof(std::max_align_t)>
class alignas(alignment__) mmalloc final {
    public:
        std::expected<mmblock, allocation_error> allocate(u64 bytes) {
            if (allocated)
                return std::unexpected(allocation_error::overwrite);

            if (bytes > size)
                return std::unexpected(allocation_error::overflow);
                
            allocated = true;
            return mmblock {
                .addr = buffer.data(),
                .size = size
            };
        }
        
        std::expected<void, allocation_error> deallocate(std::byte *addr) {
            if (addr != buffer.data())
                return std::unexpected(allocation_error::invalid_free);

            allocated = false;
            return {};
        }

    private:
        bool allocated = false;
        std::array<std::byte, size> buffer;
};
