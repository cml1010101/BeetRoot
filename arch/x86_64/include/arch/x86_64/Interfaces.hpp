#ifndef ARCH_X86_64_INTERFACES_HPP
#define ARCH_X86_64_INTERFACES_HPP
#include <arch/Types.hpp>
namespace arch
{
    namespace x86_64
    {
        class IRQGeneratingDevice
        {
        public:
            virtual uint8_t getIRQ() = 0;
        };
    }
}
#endif