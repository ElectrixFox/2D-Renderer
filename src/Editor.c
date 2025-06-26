#include "Editor.h"

static BLOCK curblock = BLOCK_PLAYER;
static int selspr = 1;

const int snap_to_grid = 1;
const int grid_size = 50;

#pragma region Main

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