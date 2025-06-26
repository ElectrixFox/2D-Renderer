#include "BlockOperations.h"

extern const int snap_to_grid;
extern const int grid_size;

static vec2 snapOperation(vec2 pos)
{
return (vec2){roundf(pos.x / grid_size) * grid_size, roundf(pos.y / grid_size) * grid_size};    // snap it to the nearest grid spot
}

unsigned int _PlaceBlockCustom(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BlockInfo block, vec2 position)
{
const BlockInfo bi = block; // renaming
unsigned int sprite = bi.spr;
unsigned int nosprites = bi.nosp;
BLOCK bltype = getBlockFromFilePath(bi.spfp);   // gets the block type

position = snap_to_grid ? snapOperation(position) : position;   // do the snap operation if should snap to grid and if not don't

unsigned int rd = CreateSpriteRenderable(rds, bi.spfp, nosprites, sprite);
unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

AddDrawable(drabs, td, rd);
AssignBlock(rd, bltype);

return rd;
}

/*
unsigned int PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BLOCK block, vec2 position)
{
BlockInfo bi = getBlockInfo(block);
unsigned int sprite = bi.spr;    // To-Do: write some function to find the sprite from the enum
unsigned int nosprites = bi.nosp; // To-Do: write some function to find the number of sprites in the sheet

unsigned int rd = CreateSpriteRenderable(rds, bi.spfp, nosprites, sprite);
unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

AddDrawable(drabs, td, rd);
AssignBlock(rd, block);

return rd;
}
*/

unsigned int PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BLOCK block, vec2 position) { return _PlaceBlockCustom(rds, tds, drabs, getBlockInfo(block), position); }

void RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, unsigned int rid)
{
int index = findDrawablesRenderable(*drabs, rid); // finding the ID
if(index == -1)
    return; // if the index isn't found just quit

RemoveDrawable(drabs, rds, tds, drabs->trsids[index]); // remove the drawable
UnassignBlock(rid);
}