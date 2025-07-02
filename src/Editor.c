#include "Editor.h"

static BLOCK curblock = BLOCK_PLAYER;
static BlockInfo cblock = {"res/sprites/player_spritesheet.png", 2, 1};

const int snap_to_grid = 1;
const int grid_size = 50;

extern UI_Table ui;
extern RenderPacket ui_rp;

#pragma region Main

BlockInfo getActiveBlock() { return cblock; }

void setActiveBlock(BlockInfo block) { cblock = block; }

void SelectBlock(Drawables drabs, unsigned int trsid)
{
/*
int index = findDrawablesTransform(drabs, trsid); // find the drawable from the transform
setActiveBlock(getBlockFromRenderID(drabs.rids[index]));    // sets the active block
*/
}

void ApplyCamera(Camera cam, RenderDetails rds) { _ApplyCamera(cam, rds.shader, rds.size); }

void ApplyProjection(Camera cam, RenderDetails rds) { _ApplyProjection(cam, rds.shader, rds.size); }

#pragma endregion

#pragma region EditorUI

static void changeBlock(int ui_id)
{
RenderInformation ri = getUIRenderInformation(ui, ui_id);   // getting the render information
BlockInfo bi = { ri.ssi.spfp, ri.ssi.nosp, ri.ssi.spr };
// BLOCK block = getBlockFromFilePath(ri.ssi.spfp);    // getting the block
setActiveBlock(bi);  // sets the active block
}

static void unfoldBlockOptions(int ui_id)
{
static int folded = 1;
static int prevuid = -1;

OutputArray(ui.data[0].meni.ui_ids);
if(prevuid != ui_id) // if the previous ID isn't the menu to unfold and the menu is folded
    {
    if(prevuid != -1)
        {
        GUI_MENU meni = getUIRenderInformation(ui, prevuid).meni;   // getting the render information
        printf("\nFolding %d", prevuid);
        for (int i = 0; i < meni.ui_ids.size; i++)
            {
            printf("\nRemoving");
            removeUIElement(&ui, &ui_rp, UI_TYPE_BUTTON, meni.ui_ids.data[i]); // remove each of the buttons
            }
        }

    printf("\nUnfolding %d", ui_id);
    GUI_MENU meni = getUIRenderInformation(ui, ui_id).meni;   // getting the render information
    OutputArray(meni.ui_ids);

    unsigned int head_id = meni.men_head_ui_id;
    printf("\nMenu head ID: %d", head_id);
    
    SpriteSheetInfo ssi = getUIRenderInformation(ui, head_id).ssi;  // getting the sprite sheet info about the head

    BLOCK block = getBlockFromFilePath(ssi.spfp);   // getting the block
    BlockInfo bi = getBlockInfo(block);

    for (int i = 2; i <= bi.nosp; i++)
        {
        RenderInformation ri;
        ri.ssi = (SpriteSheetInfo){ bi.spfp, bi.nosp, i };
        unsigned int menentry = addToMenu(&ui, &ui_rp, head_id, UI_TYPE_BUTTON, ri);
        assignButtonAction(&ui, menentry, UI_TRIGGER_PRESS, &changeBlock);
        }

    prevuid = ui_id;
    folded = 0;
    }
}

void BuildNewSelectBar(UI_Table* uitab, RenderPacket* rp)
{
vec2 topright = {1255.0f, 695.0f};
const unsigned int nblocks = getBlockCount();
const float padding = 10.0f;

for (int i = 0; i < nblocks; i++)
    {
    vec2 position = {topright.x, topright.y - (i * 50.0f + padding)}; // placing the items in a vertical line on the right side of the screen
    BlockInfo bi = getBlockInfo((BLOCK)i);
    RenderInformation ri;
    ri.ssi = (SpriteSheetInfo){ bi.spfp, bi.nosp, bi.spr };
    unsigned int entry = createUIElement(uitab, rp, position, 25.0f, UI_TYPE_BUTTON, ri);
    assignButtonAction(uitab, entry, (GUI_ACTION_TRIGGER)0, &changeBlock);
    if(ri.ssi.nosp > 1 && getBlockFromFilePath(bi.spfp) != BLOCK_IMMOVABLE_BLOCK)   // if there is more than one sprite and the block isn't the immovable type
        {
        RenderInformation tri;
        tri.meni = (GUI_MENU){(Array){NULL}, entry};
        unsigned int menhead = createUIElement(uitab, rp, position, 25.0f, UI_TYPE_MENU, tri);
        assignButtonAction(uitab, menhead, UI_TRIGGER_HOVER, &unfoldBlockOptions);
        
        printf("\nCreating the Menu");
        OutputArray(uitab->data[0].meni.ui_ids);

        /*
        for (int i = 2; i <= bi.nosp; i++)
            {
            unsigned int menentry = addToMenu(&ui, &ui_rp, menhead, UI_TYPE_BUTTON, (RenderInformation){ bi.spfp, bi.nosp, i });
            assignButtonAction(&ui, menentry, UI_TRIGGER_PRESS, &changeBlock);
            }
        */
        }
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