#ifndef KLIB_BASE_STRING_HPP
#define KLIB_BASE_STRING_HPP
#include <klib/base/Types.hpp>
namespace klib
{
    extern size_t strlen(const char* str);
    class String
    {
    private:
        size_t count;
        const char* content;
    public:
        String(const char* content);
        char operator[](size_t index) const;
        size_t length() const;
        const char* cStr() const;
        bool operator==(const String& other) const;
    };
}
#endif