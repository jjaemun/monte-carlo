#pragma once


#include <string>
#include <utility>


namespace err {


    // error codes.
    enum class mem {
        enomem,
        overwrite,
        overflow,
        corruption
    };

    
} // namespace err


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
                Attempted borrow with write permissions on allocated buffer.
            )";

        case (err::mem::overflow):
            return R"(
                Requested block exceeds buffer size.
            )";

        case (err::mem::corruption):
            return R"(
                Illegal address on free attempt.
            )";

        default:
            std::unreachable();        
    }
};
