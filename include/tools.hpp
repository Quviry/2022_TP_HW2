#include <cassert>

#pragma once

namespace nvec {
template <typename T>
T min(const T& a, const T& b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}
}  // namespace nvec
