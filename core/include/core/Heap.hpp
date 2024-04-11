#ifndef CORE_HEAP_HPP
#define CORE_HEAP_HPP
#include <klib/base/Types.hpp>
namespace core
{
    class Heap
    {
    public:
        virtual void* alloc(klib::size_t size) = 0;
        virtual void free(void* ptr) = 0;
        virtual void* realloc(void* ptr, klib::size_t size) = 0;
        static Heap* getKernelHeap();
        static Heap* getThreadHeap();
        static Heap* getCurrentHeap();
    };
}
#endif