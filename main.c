#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>
#include <GL/glu.h>

#include "src/PressableObject.h"
#include "src/Transformation.h"
#include "src/RenderObject.h"
#include "src/Entity.h"

#include "src/Camera.h"
#include "src/Input.h"
#include "src/Drawable.h"
#include "src/Editor.h"

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

void MovePointer(vec2* pos, unsigned int key)
{
switch (key)
    {
    case GLFW_KEY_W:    // move up
        pos->y += 5;
        break;
    case GLFW_KEY_A:    // move left
        pos->x -= 5;
        break;
    case GLFW_KEY_S:    // move down
        pos->y -= 5;
        break;
    case GLFW_KEY_D:    // move right
        pos->x += 5;
        break;
    default:
        break;
    }
}

vec2 GetCursorPositionRelative(GLFWwindow* window, Camera cam)
{
double x, y;
int wid, hig;
glfwGetCursorPos(window, &x, &y);
glfwGetWindowSize(window, &wid, &hig);
vec2 point = GetMousePositionRelative((vec2){(float)x - cam.poscomponent.x, (float)y + cam.poscomponent.y}, wid, hig);

return point;
}

void OutputEntitiesDetails(TransformationDetails tds, RenderDetails rds, Entities ents)
{
printf("\nSize: %d", ents.size);
printf("\n%10s\t%s\t%13s\t\t%13s %10s %8s\t", "ID", "Position", "Scale", "Shader", "Texture", "VAO");

for (int i = 0; i < ents.size; i++)
    {
    int trloc = getTransformationIDIndex(tds, ents.trsid[i]);
    int rdloc = getRenderDetailsIDIndex(rds, ents.trsid[i]);
    if (trloc == -1 || rdloc == -1) continue; // skip if transformation or render details not found

    // print the entity details
    printf("\n%10d\t(%.2f, %.2f)\t(%.2f, %.2f)\t%10d %10d %10d\t",
        ents.eid[i],
        tds.pos[trloc].x, tds.pos[trloc].y,
        tds.scale[trloc].x, tds.scale[trloc].y,
        rds.shader[rdloc], rds.texture[rdloc], rds.vao[rdloc]);
    }
}

/** Outline for sprite selection:
 * - Set all the object bar as pressable
 * - Return the eid of the entity pressed when it is pressed
 * - Use the eid to determine what texture and sprite the entity has
 * - Return the sheet and the sprite information to be used
 */

int gwid = 1280, ghig = 720;

void on_window_resize(GLFWwindow* window, int width, int height)
{
gwid = width;
ghig = height;
printf("\n%dx%d", gwid, ghig);
}

int main()
{
unsigned int width = gwid;
unsigned int height = ghig;

glfwInit();
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

RenderDetails rds = InitialiseRenderDetails();
TransformationDetails tds = InitialiseTransformationDetails(gwid, ghig);
Entities ents = InitialiseEntities(); // initialising the entities list and allocating memory
PressableDetails prds = InitialisePressableDetails();
Drawables drabs = InitialiseDrawables();
InitialiseBlockDetails();

BuildSelectBar(&rds, &tds, &drabs, &prds, &cam); // build the item select bar
printf("Size of entities: %d\nSize of render details: %d\nSize of transformations: %d\nSize of drabs: %d", ents.size, rds.size, tds.size, drabs.size);

int** grid;
int w, h;
ReadLevel("res/levels/level1.txt", &w, &h, &grid);
OutputLevel(grid, w, h);
DrawLevel(&rds, &tds, &drabs, &prds, w, h, grid);

while(!glfwWindowShouldClose(window))
    {
    // loop
    if(isPressedSingle(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, 1);

    if(isPressedSingle(GLFW_KEY_TAB))
        {
        // OutputEntitiesDetails(tds, rds, ents);
        OutputTransformations(tds);
        OutputDrawables(drabs);
        OutputPressables(prds);
        int** grid;
        int w = 0, h = 0;
        getLevel(rds, tds, drabs, prds, &w, &h, &grid);
        OutputLevel(grid, w, h);
        glfwWaitEventsTimeout(0.1); // wait for a short time to prevent multiple placements
        }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
        vec2 cpos = GetCursorPositionRelative(window, cam);
        vec2 ncpos = getCursorPosition();

        if(!PressedArea(prds, tds, cpos, 50.0f) && !PressedAreaAction(prds, tds, ncpos, 50.0f, BACT_SWITCH))
            {
            PlaceBlock(&rds, &tds, &drabs, &prds, getActiveBlock(), cpos);
            glfwWaitEventsTimeout(0.1); // wait for a short time to prevent multiple placements
            }
        else if(PressedAnother(prds, tds, cpos) || PressedAnother(prds, tds, ncpos))
            {
            unsigned int tpid = getPressedBlock(prds, tds, cpos);   // getting the temporary ID

            if(getPressableAction(prds, tpid) == BACT_SWITCH)  // if should switch to the block then switch
                SelectBlock(prds, drabs, tpid);
            }
        }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
        for (int i = 0; i < prds.size; i++)
            {
            if(CheckPressed(tds, prds.trsid[i], GetCursorPositionRelative(window, cam)))
                {
                unsigned int trid = drabs.rids[findDrawablesTransform(drabs, prds.trsid[i])];
                RemoveBlock(&rds, &tds, &drabs, &prds, trid);
                break; // break after removing the first entity
                }
            }
        glfwWaitEventsTimeout(0.1); // wait for a short time to prevent multiple placements
        }
    if(isPressedSingle(GLFW_KEY_LEFT_CONTROL))
        {
        printf("\n\n\nTrying to find");
        unsigned int* ttrsids = getPressablesTransformWithAction(prds, BACT_DELETE);
        unsigned int count = ttrsids[0];
        // ttrsids = &ttrsids[1];
        memmove(ttrsids, &ttrsids[1], count);
        unsigned int* trids = getRenderIDsFromTransformIDs(drabs, ttrsids, count);
        unsigned int* progs = getRenderablePrograms(rds, trids, count);
        for (int i = 0; i < count; i++)
            printf("\n%d\t%d\t%d", ttrsids[i], trids[i], progs[i]);
        glfwWaitEventsTimeout(0.1); // wait for a short time to prevent multiple placements
        }

    if(MoveCamera(&cam))
        ApplyStaticCamera(cam, prds, drabs, tds, rds);
    ApplyCamera(cam, prds, drabs, tds, rds);


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    DrawDrawables(rds, tds, drabs);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
