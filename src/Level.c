#include "Level.h"

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
    unsigned int tpid = pds.prid[findPressableTransfom(pds, tds.trsid[i])];
    if(getPressableAction(pds, tpid) != BACT_DELETE) continue;  // if it isn't a placed block then continue

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
// printf("\nBottom-Left: (%.2f, %.2f)\nTop-Right: (%.2f, %.2f)", minx, miny, maxx, maxy);

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
        unsigned int trid = drabs.rids[findDrawablesTransform(drabs, tid)]; // gets the render ID from the renderables
        int btype = (int)getBlockFromRenderID(trid) + 1;  // finding the type of block and adding 1
        tgrid[ygrid][xgrid] = btype;    // setting the block
        }
    }
}

*grid = tgrid;
}