#pragma once
#include "MathsOperations.h"

typedef struct Pressables {
    unsigned int* pid;
    unsigned int* trsid;
} Pressables;

/**
 * Initialises the pressable details to enable adding and removing easily
 * 
 * @returns Newly initialised Pressables object
 */
Pressables InitialisePressables();

/**
 * Returns the index of the pressable
 * 
 * @param prds The details about the pressable
 * @param prid The ID of the pressable to find
 * 
 * @returns Index of ID in the details object or -1 if not found
 */
int getPressableIDIndex(Pressables prds, unsigned int prid);

/**
 * Adds a pressable to the array
 * 
 * @param prds A pointer to the details
 * 
 * @returns The ID of the newly added pressable
 */
void AddPressable(Pressables* presids);

/**
 * Removes a pressable from the details
 * 
 * @param prds A pointer to the details
 * @param prid The ID of the object to remove
 */
void RemovePressable(Pressables* prds, unsigned int prid);

/**
 * Checks if the entity with eid has been pressed
 * 
 * @param poses The array of entity positions
 * @param scales Array of entity scales
 * @param eid The id of the entity to check
 */
int CheckPressed(vec2* poses, vec2* scales, vec2 cursorpos, unsigned int eid);
