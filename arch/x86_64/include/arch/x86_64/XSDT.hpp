#ifndef ARCH_X86_64_XSDT_HPP
#define ARCH_X86_64_XSDT_HPP
#include <arch/Types.hpp>
namespace arch
{
    namespace x86_64
    {
        struct XSDT;
        struct XSDP
        {
            char signature[8];
            uint8_t checksum;
            char oem_id[6];
            uint8_t revision;
            uint32_t rsdt_address;
            uint32_t length;
            uint64_t xsdt_address;
            uint8_t extended_checksum;
            uint8_t reserved[3];
            inline bool isSignature(const char* signature) const
            {
                return this->signature[0] == signature[0] && this->signature[1] == signature[1] && this->signature[2] == signature[2]
                    && this->signature[3] == signature[3] && this->signature[4] == signature[4] && this->signature[5] == signature[5]
                    && this->signature[6] == signature[6] && this->signature[7] == signature[7];
            }
            inline bool isValid() const
            {
                uint8_t sum = 0;
                for (size_t i = 0; i < 20; i++)
                {
                    sum += ((uint8_t *)this)[i];
                }
                return sum == 0 && isSignature("RSD PTR ") && length >= 36;
            }
            inline XSDT* getXSDT() const
            {
                return (XSDT*)xsdt_address;
            }
        } __attribute__((packed));
        struct XSDTHeader
        {
            char signature[4];
            uint32_t length;
            uint8_t revision;
            uint8_t checksum;
            char oem_id[6];
            char oem_table_id[8];
            uint32_t oem_revision;
            uint32_t creator_id;
            uint32_t creator_revision;
            inline bool isSignature(const char* signature) const
            {
                return this->signature[0] == signature[0] && this->signature[1] == signature[1] && this->signature[2] == signature[2]
                    && this->signature[3] == signature[3];
            }
        } __attribute__((packed));
        struct XSDT
        {
            XSDTHeader header;
            uint64_t entries[];
            inline bool isValid() const
            {
                uint8_t sum = 0;
                for (size_t i = 0; i < header.length; i++)
                {
                    sum += ((uint8_t *)this)[i];
                }
                return sum == 0 && header.isSignature("XSDT");
            }
        } __attribute__((packed));
    }
}
#endif