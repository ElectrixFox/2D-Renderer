#pragma once
#include "MathsOperations.h"
#include "SpriteShapes.h"

#pragma region Block Object

/**
 * Could subdivide the block enum into:
 * 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 * Sprite | Block
 */

/**
 * Block ID variable:
 * 0        | 0 0 0 0 0 | 0 0 0 0 0 | 0 0 0 0 0
 * Check    | No spr    | Sprites   | Block type
 * 
 * Lookup function for Block type to find the file path of the sprite sheet
 * 
 * ----------
 * | Blocks |
 * ----------
 * | Bl ID  |
 * | rid    |
 * ----------
 * 
 */

enum BLOCK {
    BLOCK_PLAYER = 0,
    BLOCK_MOVABLE_BARRIER = 1,
    BLOCK_MOVABLE_BLOCK = 2,
    BLOCK_IMMOVABLE_BLOCK,
    BLOCK_COUNTABLE_BLOCK,
    BLOCK_MOVABLE_DESTINATION,
    BLOCK_COUNT,
};
typedef enum BLOCK BLOCK;

struct BlockTable
    {
    unsigned int* blid;
    unsigned int* rids;
    unsigned int size;
    };
typedef struct BlockTable BlockTable;

struct BlockInfo
    {
    const char* spfp;
    unsigned int nosp;
    unsigned int spr;
    };
typedef struct BlockInfo BlockInfo;

/**
 * Sets the sprite count for the block spritesheet
 * 
 * @param blid A pointer to the block ID
 * @param nospr The number of sprites for the base block
 */
void setBlockSpriteCount(unsigned int* blid, unsigned int nospr);

/**
 * Gets the number of sprites for the block
 * 
 * @param blid The ID of the block
 * 
 * @returns The number of sprites of the block
 */
unsigned int getBlockSpriteCount(unsigned int blid);

/**
 * Sets the active sprite of the block
 * 
 * @param blid A pointer to the block ID
 * @param spr The sprite to set the block
 */
void setBlockSprite(unsigned int* blid, unsigned int spr);

/**
 * Gets the sprite for the block
 * 
 * @param blid The ID of the block
 * 
 * @returns The sprite of the block
 */
unsigned int getBlockSprite(unsigned int blid);


/**
 * Sets the block type
 * 
 * @param blid A pointer to the block ID
 * @param type The type of block
 */
void setBlockType(unsigned int* blid, unsigned int type);

/**
 * Gets the type of the block
 * 
 * @param blid The ID of the block
 * 
 * @returns The type of the block
 */
unsigned int getBlockType(unsigned int blid);

unsigned int InitialiseBlockVariable(BLOCK bltype, unsigned int nosp, unsigned int spr);

/**
 * Initialises the block table to enable the render IDs to be assigned
 */
void InitialiseBlockTable();

/**
 * Gets the number of blocks
 * 
 * @returns Number of blocks
 */
unsigned int getBlockCount();

unsigned int getRenderIDBlockVariable(unsigned int rid);

/**
 * Adds a block to the details
 * 
 * @param rid The ID of the renderable
 * @param block The block to assign
 */
void AssignBlock(unsigned int rid, unsigned int block);

/**
 * Unassigns a block from the render object
 * 
 * @param blds A pointer to the details
 * @param rid The ID of the object to remove
 */
void UnassignBlock(unsigned int rid);

const char* getBlockFilePath(BLOCK block);

BLOCK getDefaultBlockTypeFromFilePath(const char* spfp);

BLOCK getBlockTypeFromFilePath(const char* spfp);

BlockInfo getDefaultBlockInfo(BLOCK type);

BLOCK getBlockTypeFromDetails(const char* spfp, unsigned int nosp, unsigned int spr);

unsigned int getDefaultBlockInfoVar(BLOCK type);

BlockInfo getBlockInfo(unsigned int blid);

/**
 * Returns the index of the renderable
 * 
 * @param rid The ID of the renderable to find
 * 
 * @returns Index of ID in the details object or -1 if not found
 */
int getBlockRenderIndex(unsigned int rid);

/**
 * Finds the block type of the renderable
 * 
 * @param rid The ID of the renderable to find
 * 
 * @returns Returns the type of block of the renderable
 */
BLOCK getBlockTypeFromRenderID(unsigned int rid);


/**
 * Finds the block of the renderable
 * 
 * @param rid The ID of the renderable to find
 * 
 * @returns Returns the block of the renderable
 */
unsigned int getBlockFromRenderID(unsigned int rid);

/**
 * Finds the block info of the renderable
 * 
 * @param rid The ID of the renderable to find
 * 
 * @returns Returns the block info of the renderable
 */
BlockInfo getBlockInfoFromRenderID(unsigned int rid);

enum BLOCK_IM_STATE {
    BLOCK_NULL,
    BLOCK_IM_STATE_ALONE,
    BLOCK_IM_STATE_LINE_END,
    BLOCK_IM_STATE_LINE_STRAIGHT,
    BLOCK_IM_STATE_THREE_INTERSECT,
    BLOCK_IM_STATE_FOUR_INTERSECT,
    BLOCK_IM_STATE_CORNER
};
typedef enum BLOCK_IM_STATE BLOCK_IM_STATE;

/**
 * Gets the block information for the immovable block
 * 
 * @param dir The direction that the block is facing
 * 
 * @returns The block information
 */
BlockInfo getImmovableBlock(BLOCK_IM_STATE state);

unsigned int getImmovableBlockInfoVar(BLOCK_IM_STATE state);

#pragma endregion
