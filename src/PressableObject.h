#pragma once
#include "MathsOperations.h"

typedef struct Pressables {
    unsigned int* pid;
    unsigned int* trsid;
} Pressables;

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