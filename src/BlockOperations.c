#include "BlockOperations.h"

extern const int snap_to_grid;
extern const int grid_size;

static vec2 snapOperation(vec2 pos)
{
return (vec2){roundf(pos.x / grid_size) * grid_size, roundf(pos.y / grid_size) * grid_size};    // snap it to the nearest grid spot
}

unsigned int _PlaceBlockCustom(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BlockInfo block, vec2 position)
{
const BlockInfo bi = block; // renaming
unsigned int sprite = bi.spr;
unsigned int nosprites = bi.nosp;
BLOCK bltype = getBlockFromFilePath(bi.spfp);   // gets the block type

position = snap_to_grid ? snapOperation(position) : position;   // do the snap operation if should snap to grid and if not don't

unsigned int rd = CreateSpriteRenderable(rds, bi.spfp, nosprites, sprite);
unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

AddDrawable(drabs, td, rd);
AssignBlock(rd, bltype);

return rd;
}

unsigned int PlaceImmovableBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BlockInfo block, vec2 position)
{
return 0;
}

static BLOCK_IM_STATE getImmovableType(const int w, const int h, const int grid[h][w], vec2 pos)
{
int x = pos.x, y = pos.y;

int ly = 0 <= y - 1 ? y - 1 : 0;
int hy = y + 1 <= h ? y + 1 : 0;

int lx = 0 <= x - 1 ? x - 1 : 0;
int hx = x + 1 <= w ? x + 1 : 0;

mat3 scope = {
    (vec3){grid[hy][lx], grid[hy][x], grid[hy][hx]},
    (vec3){grid[y][lx], grid[y][x], grid[y][hx]},
    (vec3){grid[ly][lx], grid[ly][x], grid[ly][hx]}
};
OutputMatn(3, 3, scope.mat);

mat3 curve = {
    (vec3){0, 1.0f, 1.0f},
    (vec3){0, 0, 1.0f},
    (vec3){0, 0, 0}
};
ScalarMultMat3(curve, 4);

if(equivMat3(scope, curve))
    return BLOCK_IM_STATE_CORNER;

return BLOCK_IM_STATE_ALONE;
}

unsigned int UpdateImmovableBlocks(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, const int w, const int h, const int** grid)
{
printf("\n\n\nImmovables update");
for (int i = 0; i < h; i++)
    {
    for (int j = 0; j < w; j++)
        {
        printf("\nChecking (%d, %d) -> %d", i, j, grid[i][j]);
        if(grid[i][j] == (int)BLOCK_IMMOVABLE_BLOCK + 1) // if there is an immovable block there
            {
            BLOCK_IM_STATE imstate = getImmovableType(w, h, grid, (vec2){j, i});
            printf("\n%d", imstate);
            }
        }
    }

return 0;
}

/*
unsigned int PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BLOCK block, vec2 position)
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

unsigned int PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BLOCK block, vec2 position) { return _PlaceBlockCustom(rds, tds, drabs, getBlockInfo(block), position); }

void RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, unsigned int rid)
{
int index = findDrawablesRenderable(*drabs, rid); // finding the ID
if(index == -1)
    return; // if the index isn't found just quit

RemoveDrawable(drabs, rds, tds, drabs->trsids[index]); // remove the drawable
UnassignBlock(rid);
}