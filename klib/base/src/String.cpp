#include <klib/base/String.hpp>
namespace klib
{
    size_t strlen(const char* str)
    {
        size_t count = 0;
        while (str[count] != '\0')
        {
            count++;
        }
        return count;
    }
    String::String(const char* content)
    {
        this->count = strlen(content);
        this->content = content;
    }
    char String::operator[](size_t index) const
    {
        return this->content[index];
    }
    size_t String::length() const
    {
        return this->count;
    }
    const char* String::cStr() const
    {
        return this->content;
    }
    bool String::operator==(const String& other) const
    {
        if (this->count != other.count)
        {
            return false;
        }
        for (size_t i = 0; i < this->count; i++)
        {
            if (this->content[i] != other.content[i])
            {
                return false;
            }
        }
        return true;
    }
}