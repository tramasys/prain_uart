#pragma once

#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace prain_uart {

template <typename T, T Max>
struct limited_value {
    T value;

    // no exception, clamp value instead
    constexpr limited_value(T v) : value((v <= Max) ? v : Max) {}

    template <typename U, typename = std::enable_if_t<
        std::is_enum_v<U> && std::is_same_v<std::underlying_type_t<U>, T>>>
    constexpr limited_value(U u) : limited_value(static_cast<T>(u)) {}

    constexpr operator T() const { return value; }
};

template <std::size_t Index, std::size_t Size>
inline constexpr uint64_t get_mask() {
    static_assert(Index + Size <= 64, "Bit field exceeds 64 bits");
    return ((uint64_t{1} << Size) - 1) << Index;
}

template <std::size_t Index, std::size_t Size>
inline uint64_t read_from(uint64_t data) {
    return (data & get_mask<Index, Size>()) >> Index;
}

template <std::size_t Index, std::size_t Size>
inline void write_to(uint64_t& data, uint64_t value) {
    data = (data & ~get_mask<Index, Size>()) | ((value << Index) & get_mask<Index, Size>());
}

} // namespace prain_uart
