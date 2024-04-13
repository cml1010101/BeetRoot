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
            LocalAPIC(uint64_t base) : base((volatile uint32_t*)base)
            {
                setAPICBase(base | 0x800);
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
        struct IOAPICRedirection
        {
            uint8_t busSource;
            uint8_t irqSource;
            uint32_t globalSystemInterrupt;
            uint16_t flags;
        } __attribute__((packed));
        struct IOAPICEntry
        {
            uint8_t ioapicID;
            uint8_t reserved;
            uint32_t ioapicAddress;
            uint32_t globalSystemInterruptBase;
        } __attribute__((packed));
        struct LocalAPICEntry
        {
            uint8_t processorID;
            uint8_t apicID;
            uint32_t flags;
        } __attribute__((packed));
        struct NonMaskableInterruptSourceEntry
        {
            uint8_t nmiSource;
            uint8_t reserved;
            uint16_t flags;
            uint32_t globalSystemInterrupt;
        } __attribute__((packed));
        struct NonMaskableInterruptEntry
        {
            uint8_t processorID;
            uint16_t flags;
            uint8_t lint;
        } __attribute__((packed));
        struct LocalAPICAddressOverrideEntry
        {
            uint16_t reserved;
            uint64_t address;
        } __attribute__((packed));
        struct MADT
        {
            XSDTHeader header;
            uint32_t localAPICAddress;
            uint32_t flags;
            uint8_t entries[];
            inline bool isValid() const
            {
                uint8_t sum = 0;
                for (size_t i = 0; i < header.length; i++)
                {
                    sum += ((uint8_t *)this)[i];
                }
                return sum == 0 && header.isSignature("APIC");
            }
            inline Vector<IOAPICRedirection*> getIOAPICRedirections() const
            {
                Vector<IOAPICRedirection*> redirections;
                size_t offset = 0;
                while (offset < header.length - sizeof(MADT))
                {
                    uint8_t type = entries[offset];
                    uint8_t length = entries[offset + 1];
                    if (type == 1)
                    {
                        IOAPICRedirection* redirection = (IOAPICRedirection*)&entries[offset + 2];
                        redirections.push(redirection);
                    }
                    offset += length;
                }
                return redirections;
            }
            inline Vector<IOAPICEntry*> getIOAPICEntries() const
            {
                Vector<IOAPICEntry*> ioapicEntries;
                size_t offset = 0;
                while (offset < header.length - sizeof(MADT))
                {
                    uint8_t type = entries[offset];
                    uint8_t length = entries[offset + 1];
                    if (type == 2)
                    {
                        IOAPICEntry* entry = (IOAPICEntry*)&entries[offset + 2];
                        ioapicEntries.push(entry);
                    }
                    offset += length;
                }
                return ioapicEntries;
            }
            inline Vector<LocalAPICEntry*> getLocalAPICEntries() const
            {
                Vector<LocalAPICEntry*> localAPICEntries;
                size_t offset = 0;
                while (offset < header.length - sizeof(MADT))
                {
                    uint8_t type = entries[offset];
                    uint8_t length = entries[offset + 1];
                    if (type == 0)
                    {
                        LocalAPICEntry* entry = (LocalAPICEntry*)&entries[offset + 2];
                        localAPICEntries.push(entry);
                    }
                    offset += length;
                }
                return localAPICEntries;
            }
            inline Vector<NonMaskableInterruptSourceEntry*> getNonMaskableInterruptSourceEntries() const
            {
                Vector<NonMaskableInterruptSourceEntry*> nmiSourceEntries;
                size_t offset = 0;
                while (offset < header.length - sizeof(MADT))
                {
                    uint8_t type = entries[offset];
                    uint8_t length = entries[offset + 1];
                    if (type == 3)
                    {
                        NonMaskableInterruptSourceEntry* entry = (NonMaskableInterruptSourceEntry*)&entries[offset + 2];
                        nmiSourceEntries.push(entry);
                    }
                    offset += length;
                }
                return nmiSourceEntries;
            }
            inline Vector<NonMaskableInterruptEntry*> getNonMaskableInterruptEntries() const
            {
                Vector<NonMaskableInterruptEntry*> nmiEntries;
                size_t offset = 0;
                while (offset < header.length - sizeof(MADT))
                {
                    uint8_t type = entries[offset];
                    uint8_t length = entries[offset + 1];
                    if (type == 4)
                    {
                        NonMaskableInterruptEntry* entry = (NonMaskableInterruptEntry*)&entries[offset + 2];
                        nmiEntries.push(entry);
                    }
                    offset += length;
                }
                return nmiEntries;
            }
            inline Vector<LocalAPICAddressOverrideEntry*> getLocalAPICAddressOverrideEntries() const
            {
                Vector<LocalAPICAddressOverrideEntry*> localAPICAddressOverrideEntries;
                size_t offset = 0;
                while (offset < header.length - sizeof(MADT))
                {
                    uint8_t type = entries[offset];
                    uint8_t length = entries[offset + 1];
                    if (type == 5)
                    {
                        LocalAPICAddressOverrideEntry* entry = (LocalAPICAddressOverrideEntry*)&entries[offset + 2];
                        localAPICAddressOverrideEntries.push(entry);
                    }
                    offset += length;
                }
                return localAPICAddressOverrideEntries;
            }
        } __attribute__((packed));
    }
}
#endif