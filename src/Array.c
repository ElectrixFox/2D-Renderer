#include "Array.h"

void AppendToArray(Array* arr, unsigned int item)
{
ExpandByOne(&arr->data, arr->size, sizeof(unsigned int));   // expanding the array
arr->data[arr->size] = item;    // setting the new item
arr->size++;    // increasing the array size
}