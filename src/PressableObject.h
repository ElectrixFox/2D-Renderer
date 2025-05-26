#include "MathsOperations.h"
/* #include "Entity.h"

typedef struct PressableArray
    {
    unsigned int* eids;
    unsigned int size;
    } PressableArray;


PressableArray InitPressableArray(unsigned int size);
*/

void AddPressable(unsigned int* presids, unsigned int eid, unsigned int* n);
void RemovePressable(unsigned int* presids, unsigned int eid, unsigned int* n);

/**
 * Checks if the entity with eid has been pressed
 * 
 * @param poses The array of entity positions
 * @param scales Array of entity scales
 * @param eid The id of the entity to check
 */
int CheckPressed(vec2* poses, vec2* scales, vec2 cursorpos, unsigned int eid);

// void PressedUpdate(PressableArray pa, EntityQueue eq, GLFWwindow* window);