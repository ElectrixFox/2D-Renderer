#include "FileHandling.h"

void readFile(const char* filePath, char* output[])
{
FILE* file = fopen(filePath, "r");  // open the file to read

// error handling
if (file == NULL)
    {
    printf("ERROR: File %s is not found\n", filePath);
    return NULL;
    }

char line[128];
int i = 0;
while (fgets(line, sizeof(line), file) != NULL)
    {
    output[i] = (char*)malloc(sizeof(line) * strlen(line));   // allocate the memory for the line
    strcpy(output[i], line); // copy the line data into the lines
    i++;
    }
fclose(file);
}

void writeFile(const char* filePath)
{

}

void flattenString(char* str[], char* output)
{
int count = sizeof(str);
unsigned int tsize = 0;
for (int i = 0; i < count; i++)
    {
    tsize += strlen(str[i]);
    }
output = (char*)malloc(tsize * sizeof(char));
printf("%d %d", count, strlen(str[0]));
for (int i = 0; i < count; i++)
    {
    strcat(output, str[i]);
    }

printf("%s", output);
}