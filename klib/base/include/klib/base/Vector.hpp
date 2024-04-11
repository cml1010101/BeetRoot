#ifndef KLIB_BASE_VECTOR_HPP
#define KLIB_BASE_VECTOR_HPP
#include <klib/base/Types.hpp>
namespace klib
{
    template <typename T>
    class Vector
    {
    private:
        T* data;
        size_t capacity;
        size_t size;
    public:
        Vector();
        ~Vector();
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        void push(const T& value);
        void push(T&& value);
        T pop();
        size_t length() const;
        bool empty() const;
    };
}
#endif