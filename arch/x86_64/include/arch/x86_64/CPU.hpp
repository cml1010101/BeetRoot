#ifndef ARCH_X86_64_CPU_HPP
#define ARCH_X86_64_CPU_HPP
#include <arch/x86_64/APIC.hpp>
#include <arch/x86_64/SystemPointer.hpp>
#include <arch/x86_64/PIT.hpp>
#include <klib/base/Vector.hpp>
#include <arch/x86_64/PIC.hpp>
#include <klib/base/Memory.hpp>
namespace arch
{
    namespace x86_64
    {
        class Core
        {
        private:
            klib::UniquePointer<LocalAPIC> lapic;
        public:
            Core(klib::UniquePointer<LocalAPIC> lapic);
            void start(void (*entryPoint)());
            const LocalAPIC& getLocalAPIC() const;
            void setGDTR(SystemPointer gdtr);
            void setIDTR(SystemPointer idtr);
        };
        class CPU
        {
        private:
            klib::Vector<Core> cores;
            klib::UniquePointer<IOAPIC> ioapic;
            klib::UniquePointer<PIC> pic;
            klib::UniquePointer<PIT> pit;
            bool initAPIC(XSDT* xsdt);
        public:
            CPU(bool shouldUseAPIC, XSDP xsdp);
            Core& operator[](size_t index);
            const Core& operator[](size_t index) const;
            size_t numCores() const;
            bool canUseAPIC() const;
            void startCore(size_t coreIndex, void (*entryPoint)());
            void initAPIC();
        };
    }
}
#endif