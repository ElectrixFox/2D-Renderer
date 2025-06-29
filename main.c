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

#include "src/MenuUI.h"

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

void output(int l)
{
printf("\nI have been pressed");
}

int main()
{
unsigned int width = gwid;
unsigned int height = ghig;

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

RenderDetails block_rds = InitialiseRenderDetails();
RenderDetails ui_rds = InitialiseRenderDetails();

TransformationDetails block_tds = InitialiseTransformationDetails();
TransformationDetails ui_tds = InitialiseTransformationDetails();

Drawables block_drabs = InitialiseDrawables();
Drawables ui_drabs = InitialiseDrawables();

InitialiseBlockDetails();

BuildSelectBar(&ui_rds, &ui_tds, &ui_drabs); // build the item select bar

RenderPacket gui_rp = InitialiseRenderPacket();
CreateButton(&gui_rp, (vec2){500.0f, 500.0f}, (GUI_ACTION_TRIGGER)0, output);

int** grid;
int w, h;
ReadLevel("res/levels/level1.txt", &w, &h, &grid);
OutputLevel(grid, w, h);
DrawLevel(&block_rds, &block_tds, &block_drabs, w, h, grid);

while(!glfwWindowShouldClose(window))
    {
    // loop
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
        glfwWaitEventsTimeout(0.1); // wait for a short time to prevent multiple placements
        }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
        vec2 cpos = GetCursorPositionRelative(cam);
        vec2 ncpos = getCursorPosition();

        if(!PressedArea(block_tds, cpos, 50.0f) && !PressedArea(ui_tds, ncpos, 50.0f))
            {
            PlaceBlock(&block_rds, &block_tds, &block_drabs, getActiveBlock(), cpos);
            glfwWaitEventsTimeout(0.1); // wait for a short time to prevent multiple placements
            }
        else if(PressedAnother(ui_tds, ncpos))
            {
            unsigned int trsid = getPressedBlock(ui_tds, ncpos);   // getting the temporary ID
            unsigned int trid = ui_drabs.rids[findDrawablesTransform(ui_drabs, trsid)];
            if(getSpriteCount(getBlockFromRenderID(trid)) > 1)
                {
                printf("\nUnfolding");
                ToggleMoreOptions(&ui_rds, &ui_tds, &ui_drabs, trid);
                // UnfoldMoreOptions(&ui_rds, &ui_tds, &ui_drabs, trid);
                }
            else
                SelectBlock(ui_drabs, trsid);
            }
        glfwWaitEventsTimeout(0.1); // wait for a short time to prevent multiple placements
        }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
        vec2 cpos = GetCursorPositionRelative(cam);
        if(PressedAnother(block_tds, cpos))
            {
            unsigned int ttrsid = getPressedBlock(block_tds, cpos);
            unsigned int trid = block_drabs.rids[findDrawablesTransform(block_drabs, ttrsid)];
            RemoveBlock(&block_rds, &block_tds, &block_drabs, trid);
            }
        glfwWaitEventsTimeout(0.1); // wait for a short time to prevent multiple placements
        }

    MoveCamera(&cam);
    ApplyCamera(cam, block_rds);
    ApplyProjection(cam, block_rds);
    ApplyProjection(cam, ui_rds);
    ApplyProjection(cam, gui_rp.rds);


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    DrawDrawables(block_rds, block_tds, block_drabs);
    DrawDrawables(ui_rds, ui_tds, ui_drabs);
    drawGUIElements(gui_rp);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
