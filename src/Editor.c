#include "Editor.h"

static BLOCK curblock = BLOCK_PLAYER;

const int snap_to_grid = 1;
const int grid_size = 50;

#pragma region Main

static vec2 snapOperation(vec2 pos)
{
return (vec2){roundf(pos.x / grid_size) * grid_size, roundf(pos.y / grid_size) * grid_size};    // snap it to the nearest grid spot
}

#ifndef BLOCK_OPERATIONS_H

unsigned int PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BLOCK block, vec2 position)
{
BlockInfo bi = getBlockInfo(block);
unsigned int sprite = bi.spr;    // To-Do: write some function to find the sprite from the enum
unsigned int nosprites = bi.nosp; // To-Do: write some function to find the number of sprites in the sheet

if(snap_to_grid == 1) position = snapOperation(position);

unsigned int rd = CreateSpriteRenderable(rds, bi.spfp, nosprites, sprite);
unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

AddDrawable(drabs, td, rd);
AssignBlock(rd, block);

return rd;
}

void RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, unsigned int rid)
{
int index = findDrawablesRenderable(*drabs, rid); // finding the ID
if(index == -1)
    return; // if the index isn't found just quit

RemoveDrawable(drabs, rds, tds, drabs->trsids[index]); // remove the drawable
UnassignBlock(rid);
}

#endif

BLOCK getActiveBlock() { return curblock; }

void setActiveBlock(BLOCK block) { curblock = block; }

void SelectBlock(Drawables drabs, unsigned int trsid)
{
int index = findDrawablesTransform(drabs, trsid); // find the drawable from the transform
setActiveBlock(getBlockFromRenderID(drabs.rids[index]));    // sets the active block
}

void ApplyCamera(Camera cam, RenderDetails rds) { _ApplyCamera(cam, rds.shader, rds.size); }

void ApplyProjection(Camera cam, RenderDetails rds) { _ApplyProjection(cam, rds.shader, rds.size); }

#pragma endregion

#pragma region EditorUI

void BuildSelectBar(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs)
{
vec2 topright = {1255.0f, 695.0f};
const unsigned int nblocks = getBlockCount();
const float padding = 10.0f;

for (int i = 0; i < nblocks; i++)
    {
    vec2 position = {topright.x, topright.y - (i * 50.0f + padding)}; // placing the items in a vertical line on the right side of the screen
    unsigned int rid = PlaceBlock(rds, tds, drabs, (BLOCK)i, position);
    }
}

void UnfoldMoreOptions(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, unsigned int rid)
{
BLOCK block = getBlockFromRenderID(rid);
BlockInfo bi = getBlockInfo(block);
vec2 posi = tds->pos[getTransformationIDIndex(*tds, findDrawablesRenderable(*drabs, rid))];
vec2 padding = {50.0f, 0.0f};

for (int spr = 1; spr < bi.nosp; spr++)
    {
    bi.spr += 1;
    vec2 tpos = addVec2(posi, ScalarMultVec2(padding, -spr));
    _PlaceBlockCustom(rds, tds, drabs, bi, tpos);
    }
}

#pragma endregion