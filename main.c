#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>
#include <GL/glu.h>

#include "src/Transformation.h"
#include "src/RenderObject.h"

#include "src/Camera.h"
#include "src/Input.h"
#include "src/Drawable.h"
#include "src/Editor.h"
#include "src/SystemUI.h"

void processInput(GLFWwindow* window)
{
if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // if the escape key is pressed close the window
    {
    glfwSetWindowShouldClose(window, 1);
    }
if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
    /*double x, y;
    vec2 posy = GetMousePositionRelative(window);
    glfwGetCursorPos(window, &x, &y);
    */
    }
}

int gwid = 1280, ghig = 720;

void on_window_resize(GLFWwindow* window, int width, int height)
{
gwid = width;
ghig = height;
printf("\n%dx%d", gwid, ghig);
}

UI_Table ui;
RenderPacket ui_rp;

void output(int ui_id)
{
printf("\nI have been pressed %d", ui_id);

if(ui_id == 0)
    {
    unsigned int trsid = getUITransform(ui, ui_id);
    unsigned int rid = ui_rp.drabs.rids[findDrawablesTransform(ui_rp.drabs, trsid)];
    int index = getRenderDetailsIDIndex(ui_rp.rds, rid);
    SetUniform4f(ui_rp.rds.shader[index], "colour", (vec4){1.0f, 0.62f, 0.0f, 1.0f});
    }
}

void menoutput(int l)
{
printf("\nI the menu have been pressed %d", l);
}

/*
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

int getFullLineCount(const int scpscale, int** scope)
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
void getLineLayout(const int scpscale, const int** scope, int* layout[4])
{
int x = (scpscale - 1) / 2, y = (scpscale - 1) / 2; // the x, y coordinate of the centre
const int imblk = 4;    // the immovable block tag

int lft = (scope[y][x - 1] == imblk);   // checking the left
int rgt = (scope[y][x + 1] == imblk);   // checking the right

int tpt = (scope[y + 1][x] == imblk);   // checking the top
int btt = (scope[y - 1][x] == imblk);   // checking the bottom

*layout[0] = tpt;
*layout[1] = rgt;
*layout[2] = btt;
*layout[3] = lft;
}
*/

/**
 * If a block has somthing to one side then it is an end line
 *  If the end line has something to the other side it is a full line
 *  If the end line has something perpendicular to its side line it is a corner
 *      If the corner is also a full line it is a 3 way intersection
 *      If the three way intersection is also a 
 * If the line has something 
 */
/*
void getImmovablesState(const int w, const int h, int*** grid)
{
vec2 tstpt = {3.0f, 1.0f};
int** scope;

getScope(w, h, grid, tstpt, 3, scope);
int lnecnt = getFullLineCount(3, scope);

switch (lnecnt)
    {
    case 0: // if it is zero then it is on its own

        break;
    case 1: // if it is 1 then it is an end line

        break;
    case 2: // if it is 2 then it is either a corner or a full line
        int layout[4] = {0, 0, 0, 0};
        getLineLayout(3, scope, &layout);   // getting the layout to test if it is a corner or a full line
        if((layout[0] && layout[2]) || (layout[1] && layout[3]))  // a full line
            {
            
            }
        else if((layout[0] || layout[2]) && (layout[1] || layout[3]))   // then it is a corner
            {
            
            }

        break;
    case 3: // if it is 3 then it is a three intersection
        
        break;
    case 4: // if it is 4 then it is a four way intersection

        break;

    default:
        break;
    }

}
*/


int main()
{
/*
int** grid;
int w, h;
int** tgrid;
ReadLevel("res/levels/level1.txt", &w, &h, &grid);

ReadLevel("res/levels/level1.txt", &w, &h, &tgrid);
OutputLevel(grid, w, h);

for (int i = 0; i < h; i++)
    {
    for (int j = 0; j < w; j++)
        {
        if(grid[i][j] == (int)BLOCK_IMMOVABLE_BLOCK + 1) // if there is an immovable block there
            {
            BLOCK_IM_STATE imstate = getImmovableType(w, h, grid, (vec2){j, i});
            tgrid[i][j] = -(int)imstate;
            }
        }
    }

vec2 tpos = {1.0f, 1.0f};
BLOCK_IM_STATE tst = getImmovableType(w, h, grid, tpos);
printf("\n%d -> %d", grid[(int)tpos.y][(int)tpos.x], tst);

OutputLevel(tgrid, w, h);
return 0;
*/

unsigned int width = gwid;
unsigned int height = ghig;

setbuf(stdout, NULL);   // MUST REMOVE!!!

glfwInit();
// glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // change to borederless
GLFWwindow* window = glfwCreateWindow(width, height, "Title", 0, 0); // creates the window of size width x height
glfwSetWindowAspectRatio(window, 16, 9);
glViewport(0, 0, gwid, ghig);

glfwMakeContextCurrent(window); // sets the context of the window

glfwSetWindowSizeCallback(window, on_window_resize);

glewInit();
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

InitialiseInput(window);
Camera cam = CreateCamera((vec2){0, 0}, (vec2){gwid, ghig}, &gwid, &ghig);
ui = InitialiseUI();
ui_rp = InitialiseRenderPacket();

RenderDetails block_rds = InitialiseRenderDetails();
TransformationDetails block_tds = InitialiseTransformationDetails();
Drawables block_drabs = InitialiseDrawables();

InitialiseBlockDetails();

BuildSelectBar();

OutputDrawables(ui_rp.drabs);
OutputTransformations(ui_rp.tds);

/*
int** grid;
int w, h;
ReadLevel("res/levels/level1.txt", &w, &h, &grid);
OutputLevel(grid, w, h);
DrawLevel(&block_rds, &block_tds, &block_drabs, w, h, grid);
*/


while(!glfwWindowShouldClose(window))   // main loop
    {
    checkUI(ui, ui_rp);
    
    if(isPressedSingle(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, 1);

    if(isPressedSingle(GLFW_KEY_TAB))
        {
        OutputTransformations(block_tds);
        OutputDrawables(block_drabs);
        int** grid;
        int w = 0, h = 0;
        getLevel(block_rds, block_tds, block_drabs, &w, &h, &grid);
        OutputLevel(grid, w, h);
        // UpdateImmovableBlocks(&block_rds, &block_tds, &block_drabs, w, h, grid);
        }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
        vec2 cpos = GetCursorPositionRelative(cam);
        vec2 ncpos = getCursorPosition();

        if(!PressedArea(block_tds, cpos, 50.0f) && !PressedArea(ui_rp.tds, ncpos, 50.0f))
            {
            _PlaceBlockCustom(&block_rds, &block_tds, &block_drabs, getActiveBlock(), cpos);
            }
        }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
        vec2 cpos = GetCursorPositionRelative(cam);
        if(PressedAnother(block_tds, cpos))
            {
            printf("\nTrying to remove");
            unsigned int ttrsid = getPressedBlock(block_tds, cpos);
            unsigned int trid = block_drabs.rids[findDrawablesTransform(block_drabs, ttrsid)];
            RemoveBlock(&block_rds, &block_tds, &block_drabs, trid);
            OutputDrawables(ui_rp.drabs);
            OutputTransformations(ui_rp.tds);
            }
        }
    glfwWaitEventsTimeout(0.1); // wait for a short time to prevent multiple placements

    MoveCamera(&cam);
    ApplyCamera(cam, block_rds);
    ApplyProjection(cam, block_rds);
    ApplyProjection(cam, ui_rp.rds);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    DrawDrawables(block_rds, block_tds, block_drabs);
    DrawRenderPacket(ui_rp);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
