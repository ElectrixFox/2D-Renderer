#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void OutputTable(const char* title, const char* headers[], unsigned int nHeaders)
{
int theadlen = 0;
int spacin = 2; // spaces between headers
for (int i = 0; i < nHeaders; i++)
    theadlen += strlen(headers[i]);

int titpad = (int)((strlen(title) + theadlen) / 2); // title padding
printf("\n\n%-*s", titpad, title);

printf("\n");
for (int i = 0; i < nHeaders; i++)
    printf("%-*s", strlen(headers[i]) + spacin);    // setting up the headers





}


int main()
{
float tst = 56.3135132f;
printf("Output: %06.2f", tst);


printf("\n\n%32s", "Transformations Table");
printf("\n%-10s%-20s%-13s\t", "ID", "Position", "Scale");
printf("\n%-10d(%07.2f, %07.2f)%-2s(%05.2f, %05.2f)\t");

return 0;
}