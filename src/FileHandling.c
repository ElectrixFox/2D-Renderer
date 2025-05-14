#include "FileHandling.h"

int getlne(char** lineptr, unsigned int* size, FILE* stream)
{
if (feof(stream))   // if the end of the file exit
   return -1;
   
char line[256];

fgets(line, 256, stream);   // gets the line from the stream
unsigned int len = strlen(line + *size);
lineptr[0] = (char*)malloc(len * sizeof(char*));
strcpy(*lineptr, line); // copies the line back into the pointer
*size += len;

return (len);
}

int getline(char **lineptr, size_t *n, FILE *stream)
{
static char line[256];
char *ptr;
unsigned int len;

   if (lineptr == NULL || n == NULL)
   {
      errno = EINVAL;
      return -1;
   }

   if (ferror (stream))
      return -1;

   if (feof(stream))
      return -1;
     
   fgets(line,256,stream);

   ptr = strchr(line,'\n');   
   if (ptr)
      *ptr = '\0';

   len = strlen(line);
   
   if ((len+1) < 256)
   {
      ptr = realloc(*lineptr, 256);
      if (ptr == NULL)
         return(-1);
      *lineptr = ptr;
      *n = 256;
   }

   strcpy(*lineptr,line); 
   return(len);
}


const char* ParseShaderSource(const char* filePath)
{
FILE* file = fopen(filePath, "r");  // open the file to read
if (file == NULL)   // error handling
    {
    printf("ERROR: File %s is not found\n", filePath);
    return NULL;
    }

const int size = sizeof(char*) * (1024);    // num of chars expected
char* output = (char*)malloc(size);  // setting allocating some memory
output[0] = '\0'; // setting the start as the end

char* line = NULL;
int i = 0;
size_t bufsize = 0;
while (getlne(&line, &bufsize, file) != -1)  // while not at the end of the file
   {
   strcat(output, line);  // add the line to the pointer
   i++;
   }
const char* res = output;

return res;
}

const char* readFile(const char* filePath)
{
// To-Do
}

void writeFile(const char* filePath)
{
// To-Do
}