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

unsigned int PlaceImmovableBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BlockInfo block, vec2 position)
{
return 0;
}

static int scopeEquiv(const int w, const int h, const int** scope, const int test[h][w])
{
for (int i = 0; i < h; i++)
    for (int j = 0; j < w; j++)
        if(scope[i][j] != test[i][j])
            return 0;
return 1;
}

static void getScope(const int w, const int h, const int** grid, vec2 pos, const int scpesc, int*** scope)
{
int x = pos.x, y = pos.y;

*scope = (int**)malloc(sizeof(int) * pow(scpesc, 2));
int** tscope = (int**)malloc(sizeof(int*) * scpesc);

if(scpesc % 2 == 1)
    {
    int interv = (scpesc - 1) / 2;
    for (int j = y - interv; j <= y + interv; j++)
        {
        int jind = j - (y - interv);    // the actual j from 0 to scpesc
        tscope[jind] = (int*)malloc(sizeof(scpesc));
        
        if(j < 0 || h <= j)
            {
            for (int i = 0; i < scpesc; i++)
                tscope[jind][i] = 0;
            continue;
            }

        for (int i = x - scpesc; i <= x + scpesc; i++)
            {
            int iind = i - (x - interv);    // the actual i from 0 to scpesc

            if(i < 0 || w <= i)
                {
                tscope[jind][iind] = 0;
                continue;
                }
            tscope[jind][iind] = grid[j][i];
            }
        }
    }
else
    {
    int interv = scpesc / 2;
    for (int j = y - interv; j < y + interv; j++)
        {
        int jind = j - (y - interv);    // the actual j from 0 to scpesc
        tscope[jind] = (int*)malloc(sizeof(scpesc));
        
        if(j < 0 || h <= j)
            {
            for (int i = 0; i < scpesc; i++)
                tscope[jind][i] = 0;
            continue;
            }

        for (int i = x - interv; i < x + interv; i++)
            {
            int iind = i - (x - interv);    // the actual i from 0 to scpesc

            if(i < 0 || w <= i)
                {
                tscope[jind][iind] = 0;
                continue;
                }
            tscope[jind][iind] = grid[j][i];
            }
        }
    }
memcpy(*scope, tscope, sizeof(int) * scpesc * scpesc);
}

static void outputScope(const int scale, const int** scope)
{
printf("\n");
for (int i = 0; i < scale; i++)
    {
    for (int j = 0; j < scale; j++)
        printf("%d ", scope[i][j]);
    printf("\n");
    }
}

static void mulGrid(const int w, const int h, int (*grd)[h][w])
{
for (int i = 0; i < h; i++)
    for (int j = 0; j < w; j++)
        (*grd)[i][j] *= 4;
}

static int getFullLineCount(const int scpscale, int** scope)
{
int x = (scpscale - 1) / 2, y = (scpscale - 1) / 2; // the x, y coordinate of the centre
const int imblk = 4;    // the immovable block tag

int lft = (scope[y][x - 1] == imblk);   // checking the left
int rgt = (scope[y][x + 1] == imblk);   // checking the right

int tpt = (scope[y + 1][x] == imblk);   // checking the top
int btt = (scope[y - 1][x] == imblk);   // checking the bottom

return (lft + rgt + tpt + btt);
}

// the layout goes top, right, down, up
static void getLineLayout(const int scpscale, const int** scope, int* layout)
{
int x = (scpscale - 1) / 2, y = (scpscale - 1) / 2; // the x, y coordinate of the centre
const int imblk = 4;    // the immovable block tag

int lft = (scope[y][x - 1] == imblk);   // checking the left
int rgt = (scope[y][x + 1] == imblk);   // checking the right

int tpt = (scope[y + 1][x] == imblk);   // checking the top
int btt = (scope[y - 1][x] == imblk);   // checking the bottom


int lay[4] = {tpt, rgt, btt, lft};

/*
printf("\n");
outputScope(3, scope);
printf("\n%d %d %d %d", lay[0], lay[1], lay[2], lay[3]);
*/
for (int i = 0; i < 3; i++) // setting the output layout
    layout[i] = lay[i];
}

BLOCK_IM_STATE getImmovableType(const int w, const int h, const int** grid, vec2 pos)
{
int x = pos.x, y = pos.y;
const int imblk = 4;    // the immovable block tag

int** scope;
/**
 * If a block has somthing to one side then it is an end line
 *  If the end line has something to the other side it is a full line
 *  If the end line has something perpendicular to its side line it is a corner
 *      If the corner is also a full line it is a 3 way intersection
 *      If the three way intersection is also a 
 * If the line has something 
 */

if(grid[y][x] != imblk)
    {
    printf("\nError: Trying to find type for non-immovable");
    return -1;
    }

getScope(w, h, grid, pos, 3, &scope);   // gets the scope
int lnecnt = getFullLineCount(3, scope);

switch (lnecnt)
    {
    case 0: // if it is zero then it is on its own
        return BLOCK_IM_STATE_ALONE;
        break;
    case 1: // if it is 1 then it is an end line
        return BLOCK_IM_STATE_LINE_END;
        break;
    case 2: // if it is 2 then it is either a corner or a full line
        int layout[4] = {0, 0, 0, 0};
        getLineLayout(3, scope, layout);   // getting the layout to test if it is a corner or a full line
        // printf("\n%d %d %d %d", layout[0], layout[1], layout[2], layout[3]);
        if((layout[0] && layout[2]) || (layout[1] && layout[3]))  // a full line
            {
            return BLOCK_IM_STATE_LINE_STRAIGHT;
            }
        else if((layout[0] || layout[2]) && (layout[1] || layout[3]))   // then it is a corner
            {
            return BLOCK_IM_STATE_CORNER;
            }

        break;
    case 3: // if it is 3 then it is a three intersection
        return BLOCK_IM_STATE_THREE_INTERSECT;
        break;
    case 4: // if it is 4 then it is a four way intersection
        return BLOCK_IM_STATE_FOUR_INTERSECT;
        break;
    default:
        break;
    }

return BLOCK_IM_STATE_ALONE;
}

static vec2 getMinimumPosition(TransformationDetails tds)
{
// find the bottom left and top right blocks (the extremes)
float minx = 0, maxx = 0, miny = 0, maxy = 0;

if(tds.size == 0)   // stop if there are no transforms
    return;

for (int i = 0; i < tds.size; i++)  // find the first deletable
    {
    minx = tds.pos[i].x;
    maxx = tds.pos[i].x;
    miny = tds.pos[i].y;
    maxy = tds.pos[i].y;
    }


for (int i = 0; i < tds.size; i++)
    {
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

return (vec2){minx, miny};
}

int getBlockAtPosition(TransformationDetails tds, vec2 pos)
{
for (int i = 0; i < tds.size; i++)
    if(tds.pos[i].x == pos.x && tds.pos[i].y == pos.y)
        return tds.trsid[i];
return -1;
}

unsigned int UpdateImmovableBlocks(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, const int w, const int h, const int** grid)
{
printf("\n\n\nImmovables update");
BlockInfo bi = getBlockInfo(BLOCK_IMMOVABLE_BLOCK);
vec2 minpos = getMinimumPosition(*tds);
for (int i = 0; i < h; i++)
    {
    for (int j = 0; j < w; j++)
        {
        // printf("\nChecking (%d, %d) -> %d", i, j, grid[i][j]);
        if(grid[i][j] == (int)BLOCK_IMMOVABLE_BLOCK + 1) // if there is an immovable block there
            {
            BLOCK_IM_STATE imstate = getImmovableType(w, h, grid, (vec2){j, i});
            // printf(" -> %d", imstate);
            vec2 posi = {minpos.x + j * grid_size, minpos.y + (h - i) * grid_size};
            int trsid = getBlockAtPosition(*tds, posi);
            // printf("\n%d", trsid);
            // printf("\n%d", trsid);
            if(trsid != -1)
                {
                unsigned int rid = drabs->rids[findDrawablesTransform(*drabs, trsid)];
                _PlaceBlockCustom(rds, tds, drabs, getImmovableBlock(imstate), posi);
                }
            
            }
        }
    }

return 0;
}