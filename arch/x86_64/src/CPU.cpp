#include <arch/x86_64/CPU.hpp>
#include <arch/x86_64/GDT.hpp>
#include <arch/x86_64/IDT.hpp>
#include <core/Logger.hpp>
using namespace arch::x86_64;
using namespace klib;
bool CPU::initAPIC(XSDT* xsdt)
{
    if (xsdt == nullptr)
    {
        return false;
    }
    MADT* madt = (MADT*)xsdt->search("APIC");
    if (!madt->isValid())
    {
        return false;
    }
    auto ioapicEntries = madt->getIOAPICEntries();
    if (ioapicEntries.length() == 0)
    {
        return false;
    }
    ioapic = makeUnique<IOAPIC>(ioapicEntries[0]->ioapicAddress);
    auto processorEntries = madt->getLocalAPICEntries();
    for (size_t i = 0; i < processorEntries.length(); i++)
    {
        cores.push(Core(makeUnique(processorEntries[i])));
        cores[i].setGDTR(GDT::getGDTR());
        cores[i].setIDTR(IDT::getIDTR());
    }
    return false;
}
CPU::CPU(bool shouldUseAPIC, XSDP xsdp)
{
    pic = makeUnique<PIC>();
    pic->maskAll();
    pic->remap(0x20, 0x28);
    pit = makeUnique<PIT>();
    pic->unmask(pit->getIRQ());
    if (canUseAPIC() && shouldUseAPIC && initAPIC(xsdp.getXSDT()))
    {
    }
    else
    {
    }
}
Core& CPU::operator[](size_t index)
{
    return cores[index];
}
const Core& CPU::operator[](size_t index) const
{
    return cores[index];
}
size_t CPU::numCores() const
{
    return cores.length();
}
void CPU::startCore(size_t coreIndex, void (*entryPoint)())
{
    cores[coreIndex].start(entryPoint);
}
bool CPU::canUseAPIC() const
{
    return canEnableAPIC();
}