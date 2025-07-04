#include "MathsOperations.h"

typedef struct Array
    {
    unsigned int* data;
    unsigned int size;
    } Array;

void AppendToArray(Array* arr, unsigned int item);

void RemoveFromArrayIndex(Array* arr, int index);

void RemoveFromArray(Array* arr, unsigned int item);

void OutputArray(Array arr);