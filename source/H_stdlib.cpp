#include"H_stdlib.hpp"

DEBUG_CODE(    
    size_t allocatedMemory = 0;  
)

void* Hero::resizeArray(void* ptr, size_t number, size_t size)
{
    #ifdef DEBUG
        size_t* p = ((size_t*)ptr) - 1;
        allocatedMemory -= p[0];
        size_t* newptr = (size_t*)realloc(p, (number*size)+1);
        newptr[0] = number*size;
        allocatedMemory += number*size;
        printf("allocated memory = %zu B\n", allocatedMemory);
        return newptr + 1;
    #else
        return realloc(ptr,number*size);
    #endif
}


DEBUG_CODE(
void* operator new(size_t size)
{
    size_t* ptr = (size_t*)calloc(1, size);
    ptr[0] = size;
    allocatedMemory += size;
    printf("allocated memory = %zu B\n", allocatedMemory);
    return ptr + 1;
}

void operator delete(void* ptr)
{
    size_t* p = (size_t*)ptr - 1;
    allocatedMemory -= p[0];    
    printf("allocated memory = %zu B\n", allocatedMemory);    
    free(p);
}
)