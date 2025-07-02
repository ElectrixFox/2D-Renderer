#include "Array.h"

void AppendToArray(Array* arr, unsigned int item)
{
if(arr->size == 0)
    arr->data = malloc(sizeof(unsigned int));
else
    ExpandByOne(&arr->data, arr->size, sizeof(unsigned int));   // expanding the array
arr->data[arr->size] = item;    // setting the new item
arr->size++;    // increasing the array size
}

void OutputArray(Array arr)
{
printf("\nArray of size %d: ", arr.size);
for (int i = 0; i < arr.size; i++)
    printf("%d ", arr.data[i]);
}