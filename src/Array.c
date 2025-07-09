#include "Array.h"

static void swap(unsigned int* x, unsigned int* y)
{
if(*x == *y) return;    // if they are the same then return

// doing the swap
*x ^= *y;
*y ^= *x;
*x ^= *y;
}

static int findInArray(Array arr, unsigned int item)
{
for (int i = 0; i < arr.size; i++) // finding the element
    if(arr.data[i] == item)
        return i;
return -1;
}

Array InitialiseArray()
{
Array arr;
arr.size = 0;
arr.data = (unsigned int*)malloc(sizeof(unsigned int));
return arr;
}

void AppendToArray(Array* arr, unsigned int item)
{
if(arr->size == 0)
    arr->data = malloc(sizeof(unsigned int));
else
    ExpandByOne(&arr->data, arr->size, sizeof(unsigned int));   // expanding the array
arr->data[arr->size] = item;    // setting the new item
arr->size++;    // increasing the array size
}

void RemoveFromArrayIndex(Array* arr, int index)
{
swap(&arr->data[index], &arr->data[arr->size - 1]); // swapping the two
arr->size--;
}

void RemoveFromArray(Array* arr, unsigned int item)
{
int index = findInArray(*arr, item);

if(index != -1)
    RemoveFromArrayIndex(arr, index);
else
    printf("\nError: Cannot find item %d in the array", item);
}

void OutputArray(Array arr)
{
printf("\nArray of size %d: ", arr.size);
for (int i = 0; i < arr.size; i++)
    printf("%d ", arr.data[i]);
}