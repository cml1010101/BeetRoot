#ifndef ARCH_X86_64_PIC_HPP
#define ARCH_X86_64_PIC_HPP
#include <arch/Types.hpp>
#include <arch/x86_64/io/IO.hpp>
#include <arch/x86_64/Interfaces.hpp>
namespace arch
{
    namespace x86_64
    {
        class PIC
        {
        public:
            inline PIC()
            {
            }
            void mask(uint8_t irq)
            {
                uint16_t port;
                uint8_t value;
                if (irq < 8)
                {
                    port = 0x21;
                    value = io::inb(port) | (1 << irq);
                }
                else
                {
                    port = 0xA1;
                    value = io::inb(port) | (1 << (irq - 8));
                }
                io::outb(port, value);
            }
            void maskAll()
            {
                io::outb(0x21, 0xFF);
                io::outb(0xA1, 0xFF);
            }
            void unmask(uint8_t irq)
            {
                uint16_t port;
                uint8_t value;
                if (irq < 8)
                {
                    port = 0x21;
                    value = io::inb(port) & ~(1 << irq);
                }
                else
                {
                    port = 0xA1;
                    value = io::inb(port) & ~(1 << (irq - 8));
                }
                io::outb(port, value);
            }
            void unmaskAll()
            {
                io::outb(0x21, 0x00);
                io::outb(0xA1, 0x00);
            }
            inline void sendEOI(uint8_t irq)
            {
                if (irq >= 8)
                {
                    io::outb(0xA0, 0x20);
                }
                io::outb(0x20, 0x20);
            }
            inline void remap(uint8_t offset1, uint8_t offset2)
            {
                uint8_t mask1 = io::inb(0x21);
                uint8_t mask2 = io::inb(0xA1);
                io::outb(0x20, 0x11);
                io::outb(0xA0, 0x11);
                io::outb(0x21, offset1);
                io::outb(0xA1, offset2);
                io::outb(0x21, 4);
                io::outb(0xA1, 2);
                io::outb(0x21, 1);
                io::outb(0xA1, 1);
                io::outb(0x21, mask1);
                io::outb(0xA1, mask2);
            }
        };
    }
}
#endif