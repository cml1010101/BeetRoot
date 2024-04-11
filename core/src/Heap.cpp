#include <core/Heap.hpp>
#include <klib/base/Memory.hpp>
using namespace core;
void* klib::malloc(size_t size)
{
    return Heap::getCurrentHeap()->alloc(size);
}
void klib::free(void* ptr)
{
    Heap::getCurrentHeap()->free(ptr);
}
void* klib::realloc(void* ptr, size_t size)
{
    return Heap::getCurrentHeap()->realloc(ptr, size);
}