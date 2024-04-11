#ifndef KLIB_BASE_MEMORY_HPP
#define KLIB_BASE_MEMORY_HPP
#include <klib/base/Types.hpp>
namespace klib
{
    extern void memcpy(void* dest, const void* src, size_t size);
    extern void memset(void* dest, uint8_t value, size_t size);
    extern void memmove(void* dest, const void* src, size_t size);
    extern int memcmp(const void* ptr1, const void* ptr2, size_t size);
    extern void* malloc(size_t size);
    extern void free(void* ptr);
    extern void* realloc(void* ptr, size_t size);
    template<typename T>
    class UniquePointer
    {
    private:
        T* ptr;
    public:
        UniquePointer() : ptr(nullptr) {}
        UniquePointer(T* ptr) : ptr(ptr) {}
        UniquePointer(const UniquePointer<T>& other) = delete;
        UniquePointer(UniquePointer<T>&& other) : ptr(other.ptr)
        {
            other.ptr = nullptr;
        }
        ~UniquePointer()
        {
            if (ptr)
            {
                free(ptr);
            }
        }
        UniquePointer<T>& operator=(const UniquePointer<T>& other) = delete;
        UniquePointer<T>& operator=(UniquePointer<T>&& other)
        {
            if (ptr)
            {
                free(ptr);
            }
            ptr = other.ptr;
            other.ptr = nullptr;
            return *this;
        }
        T& operator*()
        {
            return *ptr;
        }
        T* operator->()
        {
            return ptr;
        }
        T* get()
        {
            return ptr;
        }
    };
    template<typename T, typename ... Args>
    UniquePointer<T> makeUnique(Args... args)
    {
        return UniquePointer<T>(new T(args));
    }
}
#endif