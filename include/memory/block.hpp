#pragma once


#include <cstddef>

#include "types.hpp"


struct mmblock {
    std::byte *addr;
    u64 size;
};
    
