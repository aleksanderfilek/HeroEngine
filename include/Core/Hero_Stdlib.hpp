#ifndef HERO_STDLIB_HPP
#define HERO_STDLIB_HPP

#include<cstdlib>
#include<cstdint>

namespace Hero
{

#define ARRAY_DEFAULT_SIZE 10

// dynamic size array
template<typename T>
struct Array{
    T* ptr;
    uint32_t capacity;
    uint32_t length;
    uint32_t offset;
};


// function to create array object
template<typename T>
Array<T> Array_Create(uint32_t _size = ARRAY_DEFAULT_SIZE){
    // allocate new array
    T* ptr = (T*)malloc(_size * sizeof(T));

    return (Array<T>){
        .ptr = ptr,
        .capacity = _size,
        .length = 0,
        .offset = _size
    };
}

// function to resize object
template<typename T>
void Array_Resize(Array<T>& _array, uint32_t _newCapacity){
    _array.capacity = _newCapacity;
    // change array length if new length is smaller than previous length
    _array.length = (_array.length > _newCapacity)? _newCapacity : _array.length;
    _array.ptr = (T*)realloc(_array.ptr, _array.capacity * sizeof(T));
}

// function to clear array
template<typename T>
void Array_Clear(Array<T>& _array){
    free(_array.ptr);
    _array.capacity = 0;
    _array.length = 0;
    _array.offset = 0;
}

// function to add element at the end of array
template<typename T>
void Array_AddElement(Array<T>& _array, T _newElement){
    // check if new length is equal to capacity, resize array
    if(_array.capacity == (_array.length + 1)){
        _array.capacity = _array.length + _array.offset;
        _array.ptr = (T*)realloc(_array.ptr, _array.capacity * sizeof(T));
    }

    // set new element
    _array.ptr[_array.length] = _newElement;
    _array.length++;
}

// function to set element at index
template<typename T>
void Array_SetElementAt(Array<T>& _array, uint32_t _index, T _newElement){
    // resize array if position is greater or equel to capacity
    if(_array.capacity <= _index){
        _array.capacity = _index + _array.offset;
        _array.ptr = (T*)realloc(_array.ptr, _array.capacity * sizeof(T));
    }

    // set element
    _array.ptr[_index] = _newElement;
    _array.length = _index + 1;
}

template<typename T>
T Array_GetElement(Array<T>& _array, uint32_t index){
    return _array.ptr[index];
}

}

#endif