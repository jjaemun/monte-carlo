#pragma once


#include <string_view>
#include <utility>


// codes!
namespace err {

    enum class mem {
        enomem,
        overwrite,
        overflow,
        corruption,
        live
    };

} // namespace err.


// descriptors! 
inline std::string_view err_to_str(auto code) noexcept;

    /**
     * Converts submodule error code to a string.
     */

    
inline std::string_view err_to_str(err::mem code) noexcept {

    /**
     * Converts memory submodule error code to string.
     */

    switch (code) {
        case (err::mem::enomem):
            return R"(
                No available memory to lend.
            )";

        case (err::mem::overwrite):
            return R"(
                Attempted hijack with write permissions non-owned buffer.
            )";

        case (err::mem::overflow):
            return R"(
                Requested block exceeds buffer size.
            )";

        case (err::mem::corruption):
            return R"(
                Cannot manipulate illegal address.
            )";

        case (err::mem::live):
            return R"(
                Cannot reallocate live buffer.
            )";

        default:
            std::unreachable();        
    }
};
