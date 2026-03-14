#pragma once


#include "types.hpp"


namespace mem {
    struct Block {
        std::byte *addr;
        u64 size;
    };
} // namespace mem.
    
