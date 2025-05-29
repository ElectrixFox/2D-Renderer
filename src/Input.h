#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>

typedef struct InputPacket
    {
    int key;
    int prevact;
    int action;
    int mods;
    } InputPacket;

void InitialiseInput(GLFWwindow* window);

InputPacket getCurrentInputInformation();
void resetInputPacket();

int isPressedSingle(int key);

int isHeldDown(int key);