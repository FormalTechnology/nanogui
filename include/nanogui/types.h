#pragma once

#include <chrono>

namespace types {
    /// Easing curve type.
    enum class EasingCurveType {
        Linear         ///< Linear curve type.
    };

    //typedef std::chrono::duration<unsigned int> Duration_t;
    typedef std::chrono::milliseconds Duration_t;
}
