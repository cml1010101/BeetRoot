#ifndef ARCH_X86_64_APIC_HPP
#define ARCH_X86_64_APIC_HPP
#include <arch/Types.hpp>
#include <cpuid.h>
#include <arch/x86_64/XSDT.hpp>
namespace arch
{
    namespace x86_64
    {
        inline bool canEnableAPIC()
        {
            uint32_t eax, ebx, ecx, edx;
            __get_cpuid(1, &eax, &ebx, &ecx, &edx);
            return edx & (1 << 9);
        }
        class LocalAPIC
        {
        private:
            volatile uint32_t* base;
            inline uint32_t read(uint32_t reg)
            {
                return base[reg / 4];
            }
            inline void write(uint32_t reg, uint32_t value)
            {
                base[reg / 4] = value;
            }
            inline static void setAPICBase(uint64_t base)
            {
                asm volatile("wrmsr" : : "a"(base & 0xFFFFFFFF), "d"(base >> 32), "c"(0x1B));
            }
            inline static uint64_t getAPICBase()
            {
                uint32_t eax, edx;
                asm volatile("rdmsr" : "=a"(eax), "=d"(edx) : "c"(0x1B));
                return ((uint64_t)edx << 32) | eax;
            }
        public:
            LocalAPIC() : base((volatile uint32_t*)getAPICBase())
            {
                setAPICBase(getAPICBase() | 0x800);
            }
            inline uint32_t getID()
            {
                return read(0x20);
            }
            inline uint32_t getVersion()
            {
                return read(0x30);
            }
            inline void enable()
            {
                write(0xF0, read(0xF0) | 0x100);
            }
            inline void disable()
            {
                write(0xF0, read(0xF0) & ~0x100);
            }
            inline void sendInit(uint32_t apicID)
            {
                write(0x310, apicID << 24);
                write(0x300, 0x4500);
            }
            inline void sendStartup(uint32_t apicID, uint32_t vector)
            {
                write(0x310, apicID << 24);
                write(0x300, 0x4600 | vector);
            }
            inline void sendIPI(uint32_t apicID, uint32_t vector)
            {
                write(0x310, apicID << 24);
                write(0x300, 0x4000 | vector);
            }
            inline void eoi()
            {
                write(0xB0, 0);
            }
        };
        class IOAPIC
        {
        private:
            uint32_t* base;
            inline uint32_t read(uint32_t reg)
            {
                base[0] = reg;
                return base[4];
            }
            inline void write(uint32_t reg, uint32_t value)
            {
                base[0] = reg;
                base[4] = value;
            }
        public:
            IOAPIC(uint64_t base) : base((uint32_t*)base)
            {
            }
            void writeRedirectionTable(uint32_t index, uint64_t data)
            {
                write(0x10 + index * 2, data & 0xFFFFFFFF);
                write(0x10 + index * 2 + 1, data >> 32);
            }
            uint64_t readRedirectionTable(uint32_t index)
            {
                return (uint64_t)read(0x10 + index * 2 + 1) << 32 | read(0x10 + index * 2);
            }
            uint32_t getID()
            {
                return read(0);
            }
        };
    }
}
#endif