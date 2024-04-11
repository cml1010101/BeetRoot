#ifndef ARCH_X86_64_GDT_HPP
#define ARCH_X86_64_GDT_HPP
#include <arch/Types.hpp>
namespace arch
{
    namespace x86_64
    {
        template<size_t N>
        class GDT
        {
        public:
            struct Entry
            {
                uint16_t limit_low;
                uint16_t base_low;
                uint8_t base_middle;
                uint8_t access;
                uint8_t granularity;
                uint8_t base_high;
                constexpr Entry(uint64_t base, uint64_t limit, uint8_t access, uint8_t granularity)
                    : limit_low(limit & 0xFFFF), base_low(base & 0xFFFF), base_middle((base >> 16) & 0xFF), access(access),
                        granularity(granularity), base_high((base >> 24) & 0xFF)
                {
                }
            } __attribute__((packed));
        private:
            Entry entries[N];
        public:
            constexpr GDT(Entry entries[N]) : entries(entries)
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