#include "BlockOperations.h"

unsigned int _PlaceBlockCustom(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BlockInfo block, vec2 position)
{
const BlockInfo bi = block; // renaming
unsigned int sprite = bi.spr;
unsigned int nosprites = bi.nosp;
BLOCK bltype = getBlockFromFilePath(bi.spfp);   // gets the block type

unsigned int rd = CreateSpriteRenderable(rds, bi.spfp, nosprites, sprite);
unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

AddDrawable(drabs, td, rd);
AssignBlock(rd, bltype);

return rd;
}

/*
unsigned int _PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BLOCK block, vec2 position)
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

unsigned int _PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BLOCK block, vec2 position) { return _PlaceBlockCustom(rds, tds, drabs, getBlockInfo(block), position); }

void _RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, unsigned int rid)
{
int index = findDrawablesRenderable(*drabs, rid); // finding the ID
if(index == -1)
    return; // if the index isn't found just quit

RemoveDrawable(drabs, rds, tds, drabs->trsids[index]); // remove the drawable
UnassignBlock(rid);
}