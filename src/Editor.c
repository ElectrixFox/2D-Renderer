#include "Editor.h"

static BLOCK curblock = BLOCK_PLAYER;

const int snap_to_grid = 1;
const int grid_size = 50;

extern UI_Table ui;
extern RenderPacket ui_rp;

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

static void changeBlock(int ui_id)
{
RenderInformation ri = getUIRenderInformation(ui, ui_id);   // getting the render information
SpriteSheetInfo ssi = ri.ssi;

if(ssi.nosp > 1)
    {
    
    }
BLOCK block = getBlockFromFilePath(ri.ssi.spfp);    // getting the block
setActiveBlock(block);  // sets the active block
}

void BuildNewSelectBar()
{
vec2 topright = {1255.0f, 695.0f};
const unsigned int nblocks = getBlockCount();
const float padding = 10.0f;

for (int i = 0; i < nblocks; i++)
    {
    vec2 position = {topright.x, topright.y - (i * 50.0f + padding)}; // placing the items in a vertical line on the right side of the screen
    BlockInfo bi = getBlockInfo((BLOCK)i);
    RenderInformation ri = (RenderInformation){ bi.spfp, bi.nosp, bi.spr };
    unsigned int entry = addButton(&ui, &ui_rp, position, 25.0f, ri);
    assignButtonAction(&ui, entry, (GUI_ACTION_TRIGGER)0, &changeBlock);
    }
}

void BuildSelectBar(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs)
{
vec2 topright = {1255.0f, 695.0f};
const unsigned int nblocks = getBlockCount();
const float padding = 10.0f;

for (int i = 0; i < nblocks; i++)
    {
    vec2 position = {topright.x, topright.y - (i * 50.0f + padding)}; // placing the items in a vertical line on the right side of the screen
    PlaceBlock(rds, tds, drabs, (BLOCK)i, position);
    }
}

void FoldMoreOptions(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, unsigned int* rids)
{
for (int i = 1; i < rids[0]; i++)
    {
    int index = findDrawablesRenderable(*drabs, rids[i]);

    if(index == -1)
        printf("\nNot found");

    RemoveTransformation(tds, drabs->trsids[index]);
    RemoveRenderDetail(tds, drabs->rids[index]);
    RemoveDrawable(drabs, rds, tds, rids[i]);
    }

}

static unsigned int* UnfoldMoreOptions(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, unsigned int rid)
{
BLOCK block = getBlockFromRenderID(rid);
BlockInfo bi = getBlockInfo(block);
vec2 posi = tds->pos[getTransformationIDIndex(*tds, findDrawablesRenderable(*drabs, rid))];
vec2 padding = {50.0f, 0.0f};

unsigned int* rids = (unsigned int*)malloc((bi.nosp + 1) * sizeof(unsigned int));

for (int spr = 1; spr < bi.nosp; spr++)
    {
    bi.spr += 1;
    vec2 tpos = addVec2(posi, ScalarMultVec2(padding, -spr));
    unsigned int trid = _PlaceBlockCustom(rds, tds, drabs, bi, tpos);   // setting the rid array to contain the correct details
    rids[spr] = trid;
    }
rids[0] = bi.nosp;

return rids;
}

void ToggleMoreOptions(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, unsigned int rid)
{
static unsigned int prevrid = 100;
static unsigned int* prids;

if(prevrid == rid)
    FoldMoreOptions(rds, tds, drabs, prids);  // fold the same one
else
    {
    if(prevrid != 100)
        FoldMoreOptions(rds, tds, drabs, prids);  // fold the previous
    prids = UnfoldMoreOptions(rds, tds, drabs, rid);    // unfold the new
    }

prevrid = rid;
}

#pragma endregion