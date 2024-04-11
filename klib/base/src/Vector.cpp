#include <klib/base/Vector.hpp>
namespace klib
{
    template <typename T>
    Vector<T>::Vector()
    {
        data = nullptr;
        capacity = 0;
        size = 0;
    }
    template<typename T>
    Vector<T>::~Vector()
    {
        delete[] data;
    }
    template<typename T>
    void Vector<T>::push(const T& element)
    {
        if (capacity == 0)
        {
            capacity = 1;
            data = new T[capacity];
        }
        if (size == capacity)
        {
            T *newData = new T[capacity * 2];
            for (size_t i = 0; i < size; i++)
            {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity *= 2;
        }
        data[size] = element;
        size++;
    }
    template <typename T>
    void Vector<T>::push(T&& element)
    {
        if (capacity == 0)
        {
            capacity = 1;
            data = new T[capacity];
        }
        if (size == capacity)
        {
            T *newData = new T[capacity * 2];
            for (size_t i = 0; i < size; i++)
            {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity *= 2;
        }
        data[size] = element;
        size++;
    }
    template<typename T>
    T& Vector<T>::operator[](size_t index)
    {
        return data[index];
    }
    template<typename T>
    const T& Vector<T>::operator[](size_t index) const
    {
        return data[index];
    }
    template<typename T>
    T Vector<T>::pop()
    {
        if (size == 0)
        {
            return T();
        }
        size--;
        return data[size];
    }
    template<typename T>
    size_t Vector<T>::length() const
    {
        return size;
    }
    template<typename T>
    bool Vector<T>::empty() const
    {
        return size == 0;
    }
}