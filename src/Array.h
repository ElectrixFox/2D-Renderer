#include "MathsOperations.h"

#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array
    {
    unsigned int* data;
    unsigned int size;
    } Array;

Array InitialiseArray();

void AppendToArray(Array* arr, unsigned int item);

void RemoveFromArrayIndex(Array* arr, int index);

void RemoveFromArray(Array* arr, unsigned int item);

void OutputArray(Array arr);

#endif