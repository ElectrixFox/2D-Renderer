#include "MenuUI.h"

void BuildSelectMenu(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs)
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

FoldingSidebar CreateFoldingSidebar(RenderContainer, int position, BLOCK icon)
{

}

void FoldSidebar(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, FoldingSidebar* fsb)
{

fsb->folded = 0;
}

void UnfoldSidebar(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, FoldingSidebar* fsb, unsigned int rid)
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

void ToggleFoldingSidebar(RenderContainer, FoldingSidebar* fsb)
{
if(fsb->folded == 0)
    UnfoldSidebar(rds, tds, drabs, fsb, fsb->block);
}