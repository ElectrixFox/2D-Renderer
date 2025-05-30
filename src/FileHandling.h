#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int getlne(char** lineptr, unsigned int* size, FILE* stream);

const char* readFile(const char* filePath);
const char* ParseShaderSource(const char* filePath);

void writeFile(const char* filePath);