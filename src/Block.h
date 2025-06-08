#pragma once
#include <stdio.h>
#include <string.h>

#include "MathsOperations.h"
#include "Shader.h"
#include "Texture.h"
#include "Buffer.h"
#include "SpriteShapes.h"

#pragma region Block Object

enum BLOCK {
    BLOCK_PLAYER = 0,
    BLOCK_MOVABLE_BARRIER = 1,
    BLOCK_MOVABLE_BLOCK = 2,
};
typedef enum BLOCK BLOCK;

struct BlockInfo
    {
    const char* spfp;
    unsigned int nosp;
    unsigned int spr;
    };
typedef struct BlockInfo BlockInfo;

struct BlockDetails
    {
    unsigned int* rids;
    BLOCK* blocks;
    unsigned int size;
    };
typedef struct BlockDetails BlockDetails;

/**
 * Initialises the block details to enable assigning of blocks to drawables
 */
void InitialiseBlockDetails();


/**
 * Returns the index of the renderable
 * 
 * @param rid The ID of the renderable to find
 * 
 * @returns Index of ID in the details object or -1 if not found
 */
int getBlockRenderIndex(unsigned int rid);

/**
 * Finds the block of the renderable
 * 
 * @param rid The ID of the renderable to find
 * 
 * @returns Returns the block of the renderable
 */
BLOCK getBlockFromRenderID(unsigned int rid);

/**
 * Adds a block to the details
 * 
 * @param rid The ID of the renderable
 * @param block The block to assign
 */
void AssignBlock(unsigned int rid, BLOCK block);

/**
 * Unassigns a block from the render object
 * 
 * @param blds A pointer to the details
 * @param rid The ID of the object to remove
 */
void UnassignBlock(unsigned int rid);

BlockInfo getBlockInfo(BLOCK block);

#pragma endregion
