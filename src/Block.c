#include "Block.h"

static BlockTable btab;

void setBlockSpriteCount(unsigned int* blid, unsigned int nosp)
{
unsigned int mask = 0b0111110000000000U;  // the mask for the number of sprites
*(blid) = ((*(blid) & (~mask)) | (nosp << 10));
}

unsigned int getBlockSpriteCount(unsigned int blid)
{
unsigned int mask = 0b0111110000000000U;  // the mask for the number of sprites
return ((blid & mask) >> 10);
}

void setBlockSprite(unsigned int* blid, unsigned int spr)
{
unsigned int mask = 0b0000001111100000U;  // the mask for the current sprite
*(blid) = ((*(blid) & ~mask) | (spr << 5));
}

unsigned int getBlockSprite(unsigned int blid)
{
unsigned int mask = 0b0000001111100000U;  // the mask for the current sprite
return ((blid & mask) >> 5);
}

void setBlockType(unsigned int* blid, unsigned int type)
{
unsigned int mask = 0b000000000011111U;  // the mask for the block type
*(blid) = (((*blid) & (~mask)) | type);
}

unsigned int getBlockType(unsigned int blid)
{
unsigned int mask = 0b000000000011111U;  // the mask for the block type
return (blid & mask);
}

unsigned int InitialiseBlockVariable(BLOCK bltype, unsigned int nosp, unsigned int spr)
{
unsigned int block = 0;
setBlockType(&block, bltype);
setBlockSpriteCount(&block, nosp);
setBlockSprite(&block, spr);

return block;
}

unsigned int getBlockCount() { return BLOCK_COUNT; }

void InitialiseBlockTable()
{
btab.size = 0;

btab.blid = (unsigned int*)malloc(sizeof(unsigned int));
btab.rids = (unsigned int*)malloc(sizeof(unsigned int));
}

static int findRenderIDInBlockTable(unsigned int rid)
{
for (int i = 0; i < btab.size; i++)
    if(btab.rids[i] == rid)
        return i;
return -1;
}

static int findBlockIDInBlockTable(unsigned int blid)
{
for (int i = 0; i < btab.size; i++)
    if(btab.blid[i] == blid)
        return i;
return -1;
}

void AssignBlock(unsigned int rid, unsigned int block)
{
const unsigned int n = btab.size;

// make all the arrays bigger by one to accomodate for the new element
ExpandByOne(&btab.blid, n, sizeof(unsigned int));
ExpandByOne(&btab.rids, n, sizeof(unsigned int));

// setting all the new details
btab.blid[n] = block;
btab.rids[n] = rid;

btab.size++;    // increase the number of blocks
}

void UnassignBlock(unsigned int rid)
{
int index = findRenderIDInBlockTable(rid);  // finding the ID

if(index == -1)
    return; // if the index isn't found just quit

if(index == btab.size - 1) goto end;   // hehe the naughty goto

// getting temporary stuff
unsigned int tbtab = btab.blid[index];
unsigned int tmpid = btab.rids[index];

// setting the to delete to the end values
btab.blid[index] = btab.blid[btab.size - 1];
btab.rids[index] = btab.rids[btab.size - 1];

// setting the end to the thing to delete
btab.blid[btab.size - 1] = tbtab;
btab.rids[btab.size - 1] = tmpid;

end:
btab.size--;    // decrease the size so it is effectively not there

// To-Do: Could add in a sort here to sort by ID in order to realign the table
}

const char* getBlockFilePath(BLOCK block)
{
block = getBlockType(block);
// printf("\n%d: %d %d %d", block, getBlockType(block), getBlockSpriteCount(block), getBlockSprite(block));
switch (block)
    {
    case BLOCK_PLAYER:
        return "res/sprites/player_spritesheet.png";
        break;
    case BLOCK_MOVABLE_BARRIER:
        return "res/sprites/movable_barrier_tilesheet.png";
        break;
    case BLOCK_MOVABLE_BLOCK:
        return "res/sprites/movable_spritesheet_short.png";
        break;
    case BLOCK_IMMOVABLE_BLOCK:
        return "res/sprites/immovable_tilesheet_short.png";
        break;
    case BLOCK_COUNTABLE_BLOCK:
        return "res/sprites/countable_movable_spritesheet_short.png";
        break;
    default:
        break;
    }
return "";
}

BLOCK getDefaultBlockTypeFromFilePath(const char* spfp)
{
for (int i = 0; i < getBlockCount(); i++)
    if(strcmp(getBlockFilePath(i), spfp) == 0)
        return (BLOCK)i;

return -1;
}

BLOCK getBlockTypeFromFilePath(const char* spfp) { getDefaultBlockTypeFromFilePath(spfp); }

BlockInfo getDefaultBlockInfo(BLOCK type)
{
type = getBlockType(type);
switch (type)
    {
    case BLOCK_PLAYER:
        return (BlockInfo){"res/sprites/player_spritesheet.png", 2, 1};
        break;
    case BLOCK_MOVABLE_BARRIER:
        return (BlockInfo){"res/sprites/movable_barrier_tilesheet.png", 1, 1};
        break;
    case BLOCK_MOVABLE_BLOCK:
        return (BlockInfo){"res/sprites/movable_spritesheet_short.png", 2, 1};
        break;
    case BLOCK_IMMOVABLE_BLOCK:
        return (BlockInfo){"res/sprites/immovable_tilesheet_short.png", 6, 1};
        break;
    case BLOCK_COUNTABLE_BLOCK:
        return (BlockInfo){"res/sprites/countable_movable_spritesheet_short.png", 3, 1};
        break;
    default:
        break;
    }
return (BlockInfo){NULL};
}

unsigned int getDefaultBlockInfoVar(BLOCK type)
{
BlockInfo bi = getDefaultBlockInfo(type);
return InitialiseBlockVariable(type, bi.nosp, bi.spr);
}

BlockInfo getBlockInfo(unsigned int blid)
{
printf("\n%d: %d %d %d", blid, getBlockType(blid), getBlockSpriteCount(blid), getBlockSprite(blid));
const char* spfp = getBlockFilePath(getBlockType(blid));
const unsigned int nosp = getBlockSpriteCount(blid);
const unsigned int spr = getBlockSprite(blid);

// printf("\n%s", spfp);

return (BlockInfo)
    {
    .spfp = spfp,
    .nosp = nosp,
    .spr = spr
    };
}

BLOCK getBlockTypeFromRenderID(unsigned int rid) { return (BLOCK)getBlockType(btab.blid[findRenderIDInBlockTable(rid)]); }

unsigned int getBlockFromRenderID(unsigned int rid) { return btab.blid[findRenderIDInBlockTable(rid)]; }

BlockInfo getBlockInfoFromRenderID(unsigned int rid)
{
int index = findRenderIDInBlockTable(rid);
return (BlockInfo)
    {
    .spfp = getBlockFilePath(btab.blid[index]),
    .nosp = getBlockSpriteCount(btab.blid[index]),
    .spr = getBlockSprite(btab.blid[index])
    };
}

BlockInfo getImmovableBlock(BLOCK_IM_STATE state)
{
// To-Do: This could be changed to just use the state as the parameter as it counts from 1 to 6
switch (state)
    {
    case BLOCK_IM_STATE_ALONE:
        return (BlockInfo){"res/sprites/immovable_tilesheet_short.png", 6, 1};
        break;
    case BLOCK_IM_STATE_LINE_END:
        return (BlockInfo){"res/sprites/immovable_tilesheet_short.png", 6, 2};
        break;
    case BLOCK_IM_STATE_LINE_STRAIGHT:
        return (BlockInfo){"res/sprites/immovable_tilesheet_short.png", 6, 3};
        break;
    case BLOCK_IM_STATE_THREE_INTERSECT:
        return (BlockInfo){"res/sprites/immovable_tilesheet_short.png", 6, 4};
        break;
    case BLOCK_IM_STATE_FOUR_INTERSECT:
        return (BlockInfo){"res/sprites/immovable_tilesheet_short.png", 6, 5};
        break;
    case BLOCK_IM_STATE_CORNER:
        return (BlockInfo){"res/sprites/immovable_tilesheet_short.png", 6, 6};
        break;
    default:
        return (BlockInfo){NULL};
        break;
    }
}

unsigned int getImmovableBlockInfoVar(BLOCK_IM_STATE state)
{
BlockInfo bi = getImmovableBlock(state);
return InitialiseBlockVariable(BLOCK_IMMOVABLE_BLOCK, bi.nosp, bi.spr);
}