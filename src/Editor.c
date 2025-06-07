#include "Editor.h"

static BLOCK curblock = BLOCK_PLAYER;

struct BlockInfo
    {
    const char* spfp;
    unsigned int nosp, spr;
    };
typedef struct BlockInfo BlockInfo;

static BlockInfo getBlockInfo(BLOCK block)
{
switch (block)
    {
    case BLOCK_PLAYER:
        return (BlockInfo){"res/sprites/player_tilesheet.png", 1, 1};
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


void PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds, BLOCK block, vec2 position)
{
BlockInfo bi = getBlockInfo(curblock);
unsigned int sprite = bi.spr;    // To-Do: write some function to find the sprite from the enum
unsigned int nosprites = bi.nosp; // To-Do: write some function to find the number of sprites in the sheet


unsigned int rd = CreateSpriteRenderable(rds, bi.spfp, nosprites, sprite);
unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

AddDrawable(drabs, td, rd);
AddPressable(prds, td, BACT_DELETE);
}

void RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds, unsigned int rid)
{
int index = findDrawablesRenderable(*drabs, rid); // finding the ID
if(index == -1)
    return; // if the index isn't found just quit

unsigned int prid = prds->prid[findPressableTransfom(*prds, drabs->trsids[index])];

RemoveDrawable(drabs, rds, tds, drabs->trsids[index]); // remove the drawable
RemovePressable(prds, prid);
}

void BuildSelectBar(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds)
{
vec2 topright = {1255.0f, 695.0f};
const unsigned int nsheets = 2;
const float padding = 10.0f;
const unsigned int nsprites[] = {2, 1};
const char* spritesheets[] = {
    "res/sprites/movable_spritesheet.png",
    "res/sprites/movable_barrier_tilesheet.png"
};

int spacer = 0;
for (int i = 0; i < nsheets; i++)
    {
    for (int sprite = 1; sprite < nsprites[i] + 1; sprite++)
        {
        vec2 position = {topright.x, topright.y - (spacer * 50.0f + padding)}; // placing the items in a vertical line on the right side of the screen
        
        unsigned int rd = CreateSpriteRenderable(rds, spritesheets[i], nsprites[i], sprite);
        unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

        AddDrawable(drabs, td, rd);
    
        AddPressable(prds, td, BACT_SWITCH);
        spacer++; // increase the spacer for the next item
        }
    }
}

BLOCK getActiveBlock() { return curblock; }

void setActiveBlock(BLOCK block) { curblock = block; }

void SelectBlock(PressableDetails prds, Drawables drabs)
{

}