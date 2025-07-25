#ifndef ARCH_X86_64_IO_IO_HPP
#define ARCH_X86_64_IO_IO_HPP
#include <arch/Types.hpp>
namespace arch
{
    namespace x86_64
    {
        namespace io
        {
            inline void outb(uint16_t port, uint8_t value)
            {
                asm volatile("outb %0, %1" ::"a"(value), "Nd"(port));
            }
            inline uint8_t inb(uint16_t port)
            {
                uint8_t result;
                asm volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
                return result;
            }
            inline void outw(uint16_t port, uint16_t value)
            {
                asm volatile("outw %0, %1" ::"a"(value), "Nd"(port));
            }
            inline uint16_t inw(uint16_t port)
            {
                uint16_t result;
                asm volatile("inw %1, %0" : "=a"(result) : "Nd"(port));
                return result;
            }
            inline void outl(uint16_t port, uint32_t value)
            {
                asm volatile("outl %0, %1" ::"a"(value), "Nd"(port));
            }
            inline uint32_t inl(uint16_t port)
            {
                uint32_t result;
                asm volatile("inl %1, %0" : "=a"(result) : "Nd"(port));
                return result;
            }
        }
    }
}
#endif