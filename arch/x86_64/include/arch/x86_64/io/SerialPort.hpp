#ifndef ARCH_X86_64_IO_SERIALPORT_HPP
#define ARCH_X86_64_IO_SERIALPORT_HPP
#include <arch/Types.hpp>
#include <arch/x86_64/io/IO.hpp>
namespace arch
{
    namespace x86_64
    {
        namespace io
        {
            class SerialPort
            {
            private:
                uint16_t port;
            public:
                inline SerialPort(uint16_t port) : port(port)
                {
                }
                inline bool init()
                {
                    outb(port + 1, 0x00);
                    outb(port + 3, 0x80);
                    outb(port + 0, 0x03);
                    outb(port + 1, 0x00);
                    outb(port + 3, 0x03);
                    outb(port + 2, 0xC7);
                    outb(port + 4, 0x0B);
                    outb(port + 4, 0x1E);
                    outb(port + 0, 0xAE);
                    if (inb(port + 0) != 0xAE)
                    {
                        return false;
                    }
                    outb(port + 4, 0x0F);
                    return true;
                }
                inline void write(uint8_t byte)
                {
                    while ((inb(port + 5) & 0x20) == 0);
                    outb(port, byte);
                }
                inline uint8_t read()
                {
                    while ((inb(port + 5) & 1) == 0);
                    return inb(port);
                }
            };
        }
    }
}
#endif