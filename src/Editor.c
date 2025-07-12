#include "Editor.h"

static BlockInfo cblock = {"res/sprites/player_spritesheet.png", 2, 1};
static unsigned int cblk = 0;

const int snap_to_grid = 1;
const int grid_size = 50;

extern UI_Table ui;
extern RenderPacket ui_rp;

#pragma region Main

unsigned int getActiveBlock() { return cblk; }

void setActiveBlock(unsigned int block) { cblk = block; }

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
BLOCK block = getBlockTypeFromFilePath(ri.ssi.spfp);
setActiveBlock(InitialiseBlockVariable(block, ri.ssi.nosp, ri.ssi.spr));
}

static void unfoldBlockOptions(int ui_id)
{
static int prevuid = -1;

if(prevuid != ui_id) // if the previous ID isn't the menu to unfold and the menu is folded
    {
    if(prevuid != -1)
        {
        // printf("\nFolding %d", prevuid);
        clearMenu(&ui, &ui_rp, prevuid);
        }

    // printf("\nUnfolding %d", ui_id);
    GUI_MENU meni = getUIRenderInformation(ui, ui_id).meni;   // getting the render information
    unsigned int head_id = meni.men_head_ui_id;
    
    SpriteSheetInfo ssi = getUIRenderInformation(ui, head_id).ssi;  // getting the sprite sheet info about the head

    for (int i = 2; i <= ssi.nosp; i++)
        {
        RenderInformation ri;
        ri.ssi = (SpriteSheetInfo){ ssi.spfp, ssi.nosp, i };
        unsigned int menentry = addToMenu(&ui, &ui_rp, ui_id, UI_TYPE_BUTTON, ri);
        assignButtonAction(&ui, menentry, UI_TRIGGER_PRESS, &changeBlock);
        }

    prevuid = ui_id;
    }
}

void BuildSelectBar()
{
vec2 topright = {1255.0f, 695.0f};
const unsigned int nblocks = getBlockCount();
const float padding = 10.0f;

for (int i = 0; i < nblocks; i++)
    {
    vec2 position = {topright.x, topright.y - (i * 50.0f + padding)}; // placing the items in a vertical line on the right side of the screen
    BlockInfo bi = getDefaultBlockInfo((BLOCK)i);
    RenderInformation ri;
    ri.ssi = (SpriteSheetInfo){ bi.spfp, bi.nosp, bi.spr };
    unsigned int entry = createUIElement(&ui, &ui_rp, position, 25.0f, UI_TYPE_BUTTON, ri);
    assignButtonAction(&ui, entry, (GUI_ACTION_TRIGGER)0, &changeBlock);
    if(ri.ssi.nosp > 1 && (BLOCK)i != BLOCK_IMMOVABLE_BLOCK)   // if there is more than one sprite and the block isn't the immovable type
        {
        RenderInformation tri;
        tri.meni = (GUI_MENU){(Array){NULL, 0}, entry};
        unsigned int menhead = createUIElement(&ui, &ui_rp, position, 25.0f, UI_TYPE_MENU, tri);
        assignButtonAction(&ui, menhead, UI_TRIGGER_HOVER, &unfoldBlockOptions);
        RenderInformation ntri = getUIRenderInformation(ui, menhead);

        printf("\nCreating the Menu");
        OutputArray(ntri.meni.ui_ids);
        }
    }
}

#pragma endregion