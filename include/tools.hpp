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

template <typename T>
T* subarray(T src[], std::size_t size, int begin = 0, int end = -1) {
    std::size_t local_begin, local_end;
    if (begin < 0) {
        local_begin = size - begin;
    } else {
        local_begin = begin;
    }
    if (end < 0) {
        local_end = size - end;
    } else {
        local_end = end;
    }
    if (local_end < local_begin) {
        return (T*){};
    } else {
        auto result = new T[local_end - local_begin + 1];
        for (std::size_t pose = local_begin; pose < local_end; ++pose) {
            result[pose - local_begin] = src[pose];
        }
        return result;
    }
};
}  // namespace nvec
