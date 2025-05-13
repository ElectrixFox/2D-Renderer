#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int getline(char **lineptr, size_t *n, FILE *stream);

const char* readFile(const char* filePath);
const char* ParseShaderSource(const char* filePath);

void writeFile(const char* filePath);