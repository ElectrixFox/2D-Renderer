#include "Block.h"

static BlockDetails blds;

void InitialiseBlockDetails()
{
blds.size = 0;

// allocating a small bit of memory
blds.rids = (unsigned int*)malloc(sizeof(unsigned int));
blds.blocks = (BLOCK*)malloc(sizeof(BLOCK));
}

int getBlockRenderIndex(unsigned int rid)
{
if(blds.size > rid)    // if the size is bigger than the ID then it is a valid ID
    if(blds.rids[rid] == rid)   // just in case no manipulation of the table has happened
        return rid;

for (int i = 0; i < blds.size; i++)  // simple linear search
    if(blds.rids[i] == rid)
        return i;
return -1;
}

BLOCK getBlockFromRenderID(unsigned int rid) { return blds.blocks[getBlockRenderIndex(rid)]; }

void AssignBlock(unsigned int rid, BLOCK block)
{
const unsigned int n = blds.size;

// make all the arrays bigger by one to accomodate for the new element
ExpandByOne(&blds.rids, n, sizeof(unsigned int));
ExpandByOne(&blds.blocks, n, sizeof(BLOCK));

// setting all the new details
blds.rids[n] = rid;
blds.blocks[n] = block;

blds.size++;    // increase the number of blocks
}

void UnassignBlock(unsigned int rid)
{
int index = getBlockRenderIndex(rid); // finding the ID

if(index == -1)
    return; // if the index isn't found just quit

if(index == blds.size - 1) goto end;   // hehe the naughty goto

// getting temporary stuff
unsigned int tmpid = blds.rids[index];
unsigned int tbl = blds.blocks[index];

// setting the to delete to the end values
blds.rids[index] = blds.rids[blds.size - 1];
blds.blocks[index] = blds.blocks[blds.size - 1];

// setting the end to the thing to delete
blds.rids[blds.size - 1] = tmpid;
blds.blocks[blds.size - 1] = tbl;

end:
blds.size--;    // decrease the size so it is effectively not there

// To-Do: Could add in a sort here to sort by ID in order to realign the table
}

BlockInfo getBlockInfo(BLOCK block)
{
switch (block)
    {
    case BLOCK_PLAYER:
        return (BlockInfo){"res/sprites/player_sprite.png", 1, 1};
        break;
    case BLOCK_MOVABLE_BARRIER:
        return (BlockInfo){"res/sprites/movable_barrier_tilesheet.png", 1, 1};
        break;
    case BLOCK_MOVABLE_BLOCK:
        return (BlockInfo){"res/sprites/movable_spritesheet.png", 2, 1};
        break;
    default:
        break;
    }
return (BlockInfo){NULL};
}