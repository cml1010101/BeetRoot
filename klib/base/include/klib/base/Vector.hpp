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
        class Iterator
        {
        private:
            T* data;
            size_t index;
        public:
            inline Iterator(T* data, size_t index)
            {
                this->data = data;
                this->index = index;
            }
            inline T& operator*()
            {
                return data[index];
            }
            inline const T& operator*() const
            {
                return data[index];
            }
            inline Iterator& operator++()
            {
                index++;
                return *this;
            }
            bool operator==(const Iterator& other) const
            {
                return data == other.data && index == other.index;
            }
            bool operator!=(const Iterator& other) const
            {
                return !(*this == other);
            }
        };
        Iterator begin()
        {
            return Iterator(data, 0);
        }
        Iterator end()
        {
            return Iterator(data, size);
        }
    };
}
#endif