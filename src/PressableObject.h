#pragma once
#include "MathsOperations.h"
#include "Transformation.h"

typedef struct PressableDetails {
    unsigned int* prid;
    unsigned int* trsid;
    unsigned int* pract;
    unsigned int size;
} PressableDetails;

enum BACT {
    BACT_DELETE = 1,
    BACT_SWITCH = 2
};
typedef enum BACT BACT;

/**
 * Initialises the pressable details to enable adding and removing easily
 * 
 * @returns Newly initialised PressableDetails object
 */
PressableDetails InitialisePressableDetails();

/**
 * Returns the index of the pressable
 * 
 * @param prds The details about the pressable
 * @param prid The ID of the pressable to find
 * 
 * @returns Index of ID in the details object or -1 if not found
 */
int getPressableIDIndex(PressableDetails prds, unsigned int prid);

/**
 * Finds the index of the given transform ID in the pressables table
 * 
 * @param prds The pressables table
 * @param trid The transform ID to find
 * 
 * @returns -1 if not found and the index otherwise
 */
int findPressableTransfom(PressableDetails prds, unsigned int trid);

/**
 * Adds a pressable to the array
 * 
 * @param prds A pointer to the details
 * @param tid The transformation detail of the object to press
 * @param pract The action performed when the object/block is pressed (clicked)
 * 
 * @returns The ID of the newly added pressable
 */
unsigned int AddPressable(PressableDetails* prds, unsigned int tid, unsigned int pract);

/**
 * Removes a pressable from the details
 * 
 * @param prds A pointer to the details
 * @param prid The ID of the object to remove
 */
void RemovePressable(PressableDetails* prds, unsigned int prid);

/**
 * Checks if the entity with eid has been pressed
 * 
 * @param poses The array of entity positions
 * @param scales Array of entity scales
 * @param eid The id of the entity to check
 */
int _CheckPressed(vec2* poses, vec2* scales, vec2 cursorpos, unsigned int eid);

/**
 * Checks if no objects have been pressed pressed
 * 
 * @param prds The pressables table
 * @param trds The transformations table
 * @param curpos The position of the cursor
 * 
 * @returns 1 if anything is pressed, 0 if not
 */
int PressedNothing(PressableDetails prds, TransformationDetails trds, vec2 curpos);

/**
 * Checks if multiple objects have pressed at once
 * 
 * @param prds The pressables table
 * @param trds The transformations table
 * @param curpos The position of the cursor
 * 
 * @returns 1 if something else is pressed too, 0 if not
 */
int PressedAnother(PressableDetails prds, TransformationDetails trds, vec2 curpos);

/**
 * Checks if there is a block which will overlap the given range
 * 
 * @param prds The pressables table
 * @param trds The transformations table
 * @param curpos The position of the cursor
 * @param range The range to check
 * 
 * @returns 1 if the area is not empty, 0 if it is empty
 */
int PressedArea(PressableDetails prds, TransformationDetails trds, vec2 curpos, float range);

/**
 * Sets the action for the pressable
 * 
 * @param prds A pointer to the details
 * @param prid The ID of the object to remove
 * @param pract The action to set
 */
void SetPressableAction(PressableDetails* prds, unsigned int prid, unsigned int pract);
