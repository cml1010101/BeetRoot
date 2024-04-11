#ifndef ARCH_X86_64_IDT_HPP
#define ARCH_X86_64_IDT_HPP
#include <arch/Types.hpp>
namespace arch
{
    namespace x86_64
    {
        template<size_t N>
        class IDT
        {
        public:
            struct Entry
            {
                uint16_t offset_low;
                uint16_t selector;
                uint8_t ist;
                uint8_t type_attr;
                uint16_t offset_middle;
                uint32_t offset_high;
                uint32_t zero;
                constexpr Entry(uint64_t offset, uint16_t selector, uint8_t ist, uint8_t type_attr)
                    : offset_low(offset & 0xFFFF), selector(selector), ist(ist), type_attr(type_attr),
                        offset_middle((offset >> 16) & 0xFFFF), offset_high((offset >> 32) & 0xFFFFFFFF), zero(0)
                {
                }
            } __attribute__((packed));
        private:
            Entry entries[N];
        public:
            constexpr IDT(Entry entries[N]) : entries(entries)
            {
            }
            Entry& operator[](size_t index)
            {
                return entries[index];
            }
            const Entry& operator[](size_t index) const
            {
                return entries[index];
            }
            constexpr size_t length() const
            {
                return N;
            }
            constexpr size_t size() const
            {
                return sizeof(Entry) * N;
            }
        };
    }
}
#endif