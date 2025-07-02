#include "MathsOperations.h"

typedef struct Array
    {
    unsigned int* data;
    unsigned int size;
    } Array;

void AppendToArray(Array* arr, unsigned int item);

void OutputArray(Array arr);