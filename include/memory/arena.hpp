#pragma once


#include <span>

#include "alloc.hpp"
#include "errors.hpp"


namespace mem {
    template <u64 size, u64 alignment = alignof(std::max_align_t)>
    class Arena final {
    public:
        Arena(void) {
            auto block = alloc.allocate(size);

            if (!block) 
                std::terminate();

            b = *block;
        }

        template <typename T>
        std::expected<std::span<T>, err::mem> borrow(u64 n) noexcept {
            const auto bytes = n * sizeof(T);
            if (offset + bytes > size)
                return std::unexpected(err::mem::overflow);

            auto *addr = reinterpret_cast<T*>(b.addr + offset);
            offset += bytes;
    
            return std::span<T>(addr, n);
        }

        void reset(void) noexcept { 
            offset = 0; 
        }

        u64  used(void) const noexcept { 
            return offset;        
        }

        u64  remaining(void) const noexcept { 
            return size - offset; 
        }

        bool fits(u64 n) const noexcept { 
            return offset + n <= size; 
        }

        static constexpr u64 capacity(void) noexcept { 
            return size; 
        }

    private:
        Alloc<size, alignment> alloc;
        Block b;
        u64 offset = 0;
    };
} // namespace mem.
