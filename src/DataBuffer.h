#ifndef HW2_DATA_BUFFER_H
#define HW2_DATA_BUFFER_H
#include <iostream>
namespace hw2
{
    template <typename arType> struct DataBuffer
    {
        size_t elementCount = 0; // number of elements
        const size_t elementSize = sizeof(arType); // element size in bytes
        size_t totalSize = 0; // elementCount * elementSize
        arType* data = NULL;
        void SetSize(size_t count)
        {
            elementCount = count;
            totalSize = elementCount * elementSize;
            if (data!=NULL) free(data);
            data = (arType*)malloc(totalSize);
        }
        ~DataBuffer(void)
        {
            if (data!=NULL) free(data);
        }
    };
}

#endif