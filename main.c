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
#include "src/InputManager.h"
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
InputManager inpman;

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

int main()
{
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
glfwSetKeyCallback(window, updateInput);

glewInit();
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// InitialiseInput(window);
Camera cam = CreateCamera((vec2){0, 0}, (vec2){gwid, ghig}, &gwid, &ghig);
ui = InitialiseUI();
ui_rp = InitialiseRenderPacket();
InitialiseInputManager(window);

RenderPacket block_rp = InitialiseRenderPacket();

InitialiseBlockDetails();

BuildSelectBar();

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
    
    if(isPressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, 1);

    if(isPressed(GLFW_KEY_TAB))
        {
        OutputRenderPacketDetails(block_rp);
        OutputRenderPacketDetails(ui_rp);

        int** grid;
        int w = 0, h = 0;
        getLevel(block_rp, &w, &h, &grid);
        OutputLevel(grid, w, h);
        }
    else if(isPressed(GLFW_KEY_0))
        {
        int** grid;
        int w = 0, h = 0;
        getLevel(block_rp, &w, &h, &grid);
        UpdateImmovableBlocks(&block_rp, w, h, grid);
        }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
        vec2 cpos = GetCursorPositionRelative(cam);
        vec2 ncpos = getCursorPosition();

        if(!PressedArea(block_rp.tds, cpos, 50.0f) && !PressedArea(ui_rp.tds, ncpos, 50.0f))
            {
            printf("\nPlacing block");
            _PlaceBlockCustom(&block_rp, getActiveBlock(), cpos, 0.0f);
            }
        }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
        vec2 cpos = GetCursorPositionRelative(cam);
        if(PressedAnother(block_rp.tds, cpos))
            {
            printf("\nTrying to remove");
            unsigned int ttrsid = getPressedBlock(block_rp.tds, cpos);
            unsigned int trid = block_rp.drabs.rids[findDrawablesTransform(block_rp.drabs, ttrsid)];
            RemoveBlock(&block_rp, trid);
            }
        }
    glfwWaitEventsTimeout(0.1); // wait for a short time to prevent multiple placements

    MoveCamera(&cam);
    ApplyCamera(cam, block_rp.rds);
    ApplyProjection(cam, block_rp.rds);
    ApplyProjection(cam, ui_rp.rds);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    DrawRenderPacket(block_rp);
    DrawRenderPacket(ui_rp);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
