#pragma once


#include "block.hpp"
#include "errors.hpp"


namespace mem {
    template <u64 size, u64 alignment = alignof(std::max_align_t)>
    class alignas(alignment) Allocator final {
        public:
            std::expected<Block, err::mem> allocate(u64 bytes) noexcept {
                if (allocated)
                    return std::unexpected(err::mem::live);
    
                if (bytes > size)
                    return std::unexpected(err::mem::overflow);
                    
                allocated = true;
                return Block {
                    buffer.data(),
                    bytes
                };
            }
        
            std::expected<void, err::mem> deallocate(const Block &block) noexcept {
                if (block.addr != buffer.data())
                    return std::unexpected(err::mem::corruption);
    
                allocated = false;
                return {};
            }

        private:
            bool allocated = false;
            std::array<std::byte, size> buffer;
    };
} //namespace mem.
