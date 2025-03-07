#pragma once

#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include "protocol.hpp"

namespace prain_uart {

// Strong type that only allows values <= Max
template<typename T, T Max>
struct limited_value {
    T value;

    constexpr limited_value(T v) : value(v) {
        if(v > Max)
            throw std::out_of_range("Value exceeds allowed bit-field range");
    }

    // Allow construction from enum if its underlying type is T.
    template<typename U, typename = std::enable_if_t<
        std::is_enum<U>::value && std::is_same_v<std::underlying_type_t<U>, T>
    >>
    constexpr limited_value(U u) : value(static_cast<T>(u)) {
        if(value > Max)
            throw std::out_of_range("Value exceeds allowed bit-field range");
    }

    constexpr operator T() const { return value; }
};

#define GETMASK(index, size) ((((size_t)1 << (size)) - 1) << (index))
#define READFROM(data, index, size) (((data) & GETMASK((index), (size))) >> (index))
#define WRITETO(data, index, size, value) ((data) = (((data) & (~GETMASK((index), (size)))) | (((value) << (index)) & (GETMASK((index), (size))))))

#define FIELD(data, name, index, size) \
	inline decltype(data) name() const { return READFROM(data, index, size); } \
	inline void set_##name(decltype(data) value) { WRITETO(data, index, size, value); }

} // namespace prain_uart
