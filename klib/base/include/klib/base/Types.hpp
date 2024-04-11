#ifndef KLIB_BASE_TYPES_HPP
#define KLIB_BASE_TYPES_HPP
#include <arch/Types.hpp>
namespace klib
{
    using size_t = arch::size_t;
    using ssize_t = arch::ssize_t;
    using uintptr_t = arch::uintptr_t;
    using intptr_t = arch::intptr_t;
    using uint64_t = arch::uint64_t;
    using int64_t = arch::int64_t;
    using uint32_t = arch::uint32_t;
    using int32_t = arch::int32_t;
    using uint16_t = arch::uint16_t;
    using int16_t = arch::int16_t;
    using uint8_t = arch::uint8_t;
    using int8_t = arch::int8_t;
}
#endif