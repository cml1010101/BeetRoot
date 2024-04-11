#ifndef ARCH_X86_64_PIT_HPP
#define ARCH_X86_64_PIT_HPP
#include <arch/Types.hpp>
#include <arch/x86_64/io/IO.hpp>
#include <arch/x86_64/Interfaces.hpp>
namespace arch
{
    namespace x86_64
    {
        class PIT : public IRQGeneratingDevice
        {
        public:
            inline PIT()
            {
                io::outb(0x43, 0x34);
                io::outb(0x40, 0xFF);
                io::outb(0x40, 0xFF);
            }
            void setFrequency(uint8_t channel, uint32_t frequency)
            {
                uint16_t divisor = 1193180 / frequency;
                uint8_t l = (uint8_t)(divisor & 0xFF);
                uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);
                io::outb(0x43, 0x36 | (channel << 6));
                io::outb(0x40 + channel, l);
                io::outb(0x40 + channel, h);
            }
            void setCounter(uint8_t channel, uint16_t counter)
            {
                uint8_t l = (uint8_t)(counter & 0xFF);
                uint8_t h = (uint8_t)((counter >> 8) & 0xFF);
                io::outb(0x43, 0x36 | (channel << 6));
                io::outb(0x40 + channel, l);
                io::outb(0x40 + channel, h);
            }
            inline void enable(uint8_t channel)
            {
                io::outb(0x43, 0x36 | (channel << 6) | 0x01);
            }
            inline void disable(uint8_t channel)
            {
                io::outb(0x43, 0x36 | (channel << 6));
            }
            inline uint8_t getIRQ()
            {
                return 0;
            }
        };
    }
}
#endif