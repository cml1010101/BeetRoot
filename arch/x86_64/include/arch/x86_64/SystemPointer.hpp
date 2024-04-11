#ifndef ARCH_X86_64_SYSTEMPOINTER_HPP
#define ARCH_X86_64_SYSTEMPOINTER_HPP
#include <arch/Types.hpp>
namespace arch
{
    namespace x86_64
    {
        struct SystemPointer
        {
            uint16_t limit;
            uint64_t base;
            constexpr SystemPointer(uint16_t limit, uint64_t base) : limit(limit), base(base)
            {
            }
        } __attribute__((packed));
    }
}
#endif