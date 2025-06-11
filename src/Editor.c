#include "Editor.h"

static BLOCK curblock = BLOCK_PLAYER;

unsigned int PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds, BLOCK block, vec2 position)
{
BlockInfo bi = getBlockInfo(block);
unsigned int sprite = bi.spr;    // To-Do: write some function to find the sprite from the enum
unsigned int nosprites = bi.nosp; // To-Do: write some function to find the number of sprites in the sheet

unsigned int rd = CreateSpriteRenderable(rds, bi.spfp, nosprites, sprite);
unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

AddDrawable(drabs, td, rd);
AddPressable(prds, td, BACT_DELETE);
AssignBlock(rd, block);

return rd;
}

void RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds, unsigned int rid)
{
int index = findDrawablesRenderable(*drabs, rid); // finding the ID
if(index == -1)
    return; // if the index isn't found just quit

unsigned int prid = prds->prid[findPressableTransfom(*prds, drabs->trsids[index])];

if(getPressableAction(*prds, prid) != BACT_DELETE)  // if the block shouldn't be deleted don't delete it
    return; 

RemoveDrawable(drabs, rds, tds, drabs->trsids[index]); // remove the drawable
RemovePressable(prds, prid);
UnassignBlock(prid);
}

void BuildSelectBar(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds)
{
vec2 topright = {1255.0f, 695.0f};
const unsigned int nblocks = 3;
const float padding = 10.0f;

for (int i = 0; i < nblocks; i++)
    {
    vec2 position = {topright.x, topright.y - (i * 50.0f + padding)}; // placing the items in a vertical line on the right side of the screen
    unsigned int rid = PlaceBlock(rds, tds, drabs, prds, (BLOCK)i, position);
    int index = findPressableTransfom(*prds, drabs->trsids[findDrawablesRenderable(*drabs, rid)]);
    SetPressableAction(prds, prds->prid[index], BACT_SWITCH);
    }
}

BLOCK getActiveBlock() { return curblock; }

void setActiveBlock(BLOCK block) { curblock = block; }

void SelectBlock(PressableDetails prds, Drawables drabs, unsigned int prid)
{
int index = getPressableIDIndex(prds, prid);
if(prds.pract[index] != BACT_SWITCH)    // if the pressed object isn't a switchable
    return;

index = findDrawablesTransform(drabs, prds.trsid[index]);   // find the drawable from the transform
setActiveBlock(getBlockFromRenderID(drabs.rids[index]));
}