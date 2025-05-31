#pragma once
#include "RenderObject.h"
#include "Transformation.h"
#include "PressableObject.h"

struct Entities
    {
    unsigned int* eid;
    unsigned int* rid;
    unsigned int* trsid;
    unsigned int* pid;
    unsigned int size;
    };
typedef struct Entities Entities;

/**
 * Initialises the Entities
 * 
 * @returns Newly initialised Entities object
 */
Entities InitialiseEntities();

/**
 * Returns the index of the entity record
 * 
 * @param ents The details about the entities
 * @param eid The ID of the entity to find
 * 
 * @returns Index of ID in the details object or -1 if not found
 */
int getEntitiesIDIndex(Entities ents, unsigned int eid);

/**
 * Adds an entity to the details
 * 
 * @param ents A pointer to the Entities object
 * @param rid The ID of the render object for the entity
 * @param trsid The ID of the transformation object for the entity
 * @param pid The ID of the pressable object for the entity
 * 
 * @returns The ID of the newly added entity
 */
unsigned int AddEntity(Entities* ents, unsigned int rid, unsigned int trsid, unsigned int pid);

/**
 * Removes an entity from the details
 * 
 * @param ents A pointer to the Entities object
 * @param eid The ID of the entity to remove
 */
void RemoveEntity(Entities* ents, unsigned int eid);

/**
 * Creates an entity from its components
 * 
 * @param ent Pointer to Entities object
 * @param rid The associated render ID of the entity
 * @param tid The associated transformation ID of the entity
 * 
 * @returns The ID of the newly created entity
 */
unsigned int CreateEntity(Entities* ent, unsigned int rid, unsigned int tid);
