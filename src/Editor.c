#include "Editor.h"

static BLOCK curblock = BLOCK_PLAYER;

const int snap_to_grid = 1;
const int grid_size = 50;

unsigned int PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds, BLOCK block, vec2 position)
{
BlockInfo bi = getBlockInfo(block);
unsigned int sprite = bi.spr;    // To-Do: write some function to find the sprite from the enum
unsigned int nosprites = bi.nosp; // To-Do: write some function to find the number of sprites in the sheet

if(snap_to_grid == 1)   // if should snap to grid
    position = (vec2){roundf(position.x / grid_size) * grid_size, roundf(position.y / grid_size) * grid_size};  // snap it to the nearest grid spot

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
const unsigned int nblocks = getBlockCount();
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

void OutputLevel(const int** grid, int w, int h)
{
printf("\nLevel\n");
for (int y = 0; y < h; y++)
    {
    for (int x = 0; x < w; x++)
        {
        printf("%d ", grid[y][x]);
        }
    printf("\n");
    }

}

void getLevel(RenderDetails rds, TransformationDetails tds, Drawables drabs, PressableDetails pds, int* w, int* h, int*** grid)
{
// find the bottom left and top right blocks (the extremes)
float minx = 0, maxx = 0, miny = 0, maxy = 0;
for (int i = 0; i < tds.size; i++)
    {
    printf("\nChecking %d/%d", tds.trsid[i], tds.size);
    if(getPressableAction(pds, findPressableTransfom(pds, tds.trsid[i])) != BACT_DELETE) continue;  // if it isn't a placed block then continue
    printf("\t%d is good", tds.trsid[i]);

    // getting the extreme points
    if(tds.pos[i].x < minx)
        minx = tds.pos[i].x;

    if(maxx < tds.pos[i].x)
        maxx = tds.pos[i].x;
    
    if(tds.pos[i].y < miny)
        miny = tds.pos[i].y;
    
    if(maxy < tds.pos[i].y)
        maxy = tds.pos[i].y;
    }

int gridw = (maxx - minx) / grid_size + 1;  // one longer as we include the final position too
int gridh = (maxy - miny) / grid_size + 1;

int** tgrid = (int**)malloc(sizeof(int*) * gridw * gridh);    // initialising the grid

*w = gridw;
*h = gridh;

{   // creating a new scope as to be able to use i and j
printf("\nBottom-Left: (%.2f, %.2f)\nTop-Right: (%.2f, %.2f)", minx, miny, maxx, maxy);

for (int i = 0; i < gridh; i++)
    tgrid[i] = (int*)calloc(gridw, sizeof(int));    // allocate the memory for the row

for (float y = maxy; miny <= y; y -= (float)grid_size)
    {
    int ygrid = (int)((maxy - y) / grid_size);

    for (float x = minx; x <= maxx; x += (float)grid_size)  // go along the row
        {
        int xgrid = (int)((x - minx) / grid_size);
        vec2 tpos = (vec2){x, y};   // the temporary position
        int tid = getTransformAt(tds, tpos);    // get the transform at the position to check
        if(tid == -1)   // if nothing is found then go to the next grid coordinate to check
            continue;
        int btype = (int)getBlockFromRenderID(drabs.rids[findDrawablesTransform(drabs, tid)]) + 1;  // finding the type of block and adding 1
        tgrid[ygrid][xgrid] = btype;    // setting the block
        printf("\nGType: %d\nBType: %d", tgrid[ygrid][xgrid], btype);
        }
    }
}

*grid = tgrid;
}
