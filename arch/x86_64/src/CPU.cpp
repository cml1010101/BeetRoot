#include <arch/x86_64/CPU.hpp>
#include <arch/x86_64/GDT.hpp>
#include <arch/x86_64/IDT.hpp>
using namespace arch::x86_64;
CPU::CPU(bool shouldUseAPIC)
{
    pic = klib::makeUnique<PIC>();
    pic->maskAll();
    pit = klib::makeUnique<PIT>();
}