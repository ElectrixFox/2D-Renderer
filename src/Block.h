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
    const char** spfps;
    unsigned int* nosps;
    unsigned int* sprs;
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
 * 
 * @returns Newly initialised BlockDetails object
 */
BlockDetails InitialiseBlockDetails();


/**
 * Returns the index of the renderable
 * 
 * @param blds The information about the blocks
 * @param rid The ID of the renderable to find
 * 
 * @returns Index of ID in the details object or -1 if not found
 */
int getBlockRenderIndex(BlockDetails blds, unsigned int rid);

/**
 * Adds a block to the details
 * 
 * @param blds A pointer to the block details
 * @param rid The ID of the renderable
 * @param block The block to assign
 */
void AssignBlock(BlockDetails* blds, unsigned int rid, BLOCK block);

/**
 * Unassigns a block from the render object
 * 
 * @param blds A pointer to the details
 * @param rid The ID of the object to remove
 */
void UnassignBlock(BlockDetails* blds, unsigned int rid);

BlockInfo getBlockInfo(BLOCK block);

#pragma endregion
