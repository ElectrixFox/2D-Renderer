#include "Entity.h"

typedef struct PressableArray
    {
    unsigned int* eids;
    unsigned int size;
    } PressableArray;


PressableArray InitPressableArray(unsigned int size);

void AddPressable(PressableArray* pa, unsigned int eid);
void RemovePressable(PressableArray* pa, unsigned int eid);

void PressedUpdate(PressableArray pa, EntityQueue eq, GLFWwindow* window);