#include "Entity.h"

typedef struct PressableArray
    {
    unsigned int* eids;
    unsigned int size;
    } PressableArray;


PressableArray InitPressableArray(unsigned int size);

void AddPressable(unsigned int* presids, unsigned int eid, unsigned int* n);
void RemovePressable(unsigned int* presids, unsigned int eid, unsigned int* n);

/**
 * Checks if the entity with eid has been pressed
 * 
 * @param poses The array of positions
 * @param presids Array of pressable entity IDs
 * @param n The number of pressable entity IDs
 */
int CheckPressed(unsigned int* presids, unsigned int n, vec2* poses, unsigned int eid);

void PressedUpdate(PressableArray pa, EntityQueue eq, GLFWwindow* window);