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

vec2 GetCursorPosition(GLFWwindow* window)
{
double x, y;
int wid, hig;
glfwGetCursorPos(window, &x, &y);
glfwGetWindowSize(window, &wid, &hig);
vec2 point = GetMousePositionRelative((vec2){x, y}, wid, hig);

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

struct Drawables {
    unsigned int* trsids;
    unsigned int* rids;
    unsigned int size;
};
typedef struct Drawables Drawables;

Drawables InitialiseDrawables()
{
Drawables drabs;
drabs.size = 0;

drabs.trsids = (unsigned int*)malloc(sizeof(unsigned int));
drabs.rids = (unsigned int*)malloc(sizeof(unsigned int));

return drabs;
}

void AddDrawable(Drawables* drabs, unsigned int trid, unsigned int rid)
{
static unsigned int id = 0; // a static incrementing counter to set the new ID as
const unsigned int n = drabs->size;

// make all the arrays bigger by one to accomodate for the new element
ExpandByOne(&drabs->rids, n, sizeof(unsigned int));
ExpandByOne(&drabs->trsids, n, sizeof(unsigned int));

// setting all the new details
drabs->rids[n] = rid;
drabs->trsids[n] = trid;

drabs->size++;    // increase the number of drawables
}

void DrawDrawables(RenderDetails rds, TransformationDetails tds, Drawables drabs, Camera cam)
{
// getting all we will need from the transformation objects first
m4 view = getCameraMatrix(cam);
m4 projection = getTransformProjectionMatrix(tds);
m4* models = (m4*)malloc(drabs.size * sizeof(m4));  // getting all of the transformation matrices

for (int i = 0; i < drabs.size; i++)    // setting the model matrices
    models[i] = getTransformModelMatrix(tds, drabs.trsids[i]);

// now do the rendering
for (int i = 0; i < drabs.size; i++)    // setting all the uniforms
    {
    const unsigned int prog = rds.shader[getRenderDetailsIDIndex(rds, drabs.rids[i])];  // may as well make this a constant here for efficiency
    SetUniformM4(prog, "model", models[i]);
    SetUniformM4(prog, "view", view);
    SetUniformM4(prog, "projection", projection);
    }

for (int i = 0; i < drabs.size; i++)
    DrawRenderable(rds, drabs.rids[i]); // finally do the actual drawing
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
// glViewport(0, 0, width, height);

glfwSetWindowSizeCallback(window, on_window_resize);

glewInit();
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

InitialiseInput(window);
Camera cam = CreateCamera((vec2){0, 0}, (vec2){gwid, ghig}, &gwid, &ghig);

RenderDetails rds = InitialiseRenderDetails();
TransformationDetails tds = InitialiseTransformationDetails(gwid, ghig);
Entities ents = InitialiseEntities(); // initialising the entities list and allocating memory
Drawables drabs = InitialiseDrawables();

unsigned int rd1 = CreatePlainSquareRenderable(&rds);
unsigned int td1 = AddTransformation(&tds, (vec2){gwid / 2 - 25.0f, ghig / 2}, (vec2){25.0f, 25.0f});
setPosition(tds, td1, (vec2){50.0f, 50.0f});
    {
    int rind = getRenderDetailsIDIndex(rds, rd1);
    SetUniform4f(rds.shader[rind], "colour", (vec4){1.0f, 0.0f, 0.0f, 1.0f});
}
AddDrawable(&drabs, td1, rd1);

unsigned int ent1 = AddEntity(&ents, td1, 0);
unsigned int rd2 = CreateSpriteRenderable(&rds, "res/sprites/movable_spritesheet.png", 2, 1);
unsigned int td2 = AddTransformation(&tds, (vec2){gwid / 2 + 25.0f, ghig / 2}, (vec2){25.0f, 25.0f});

AddDrawable(&drabs, td2, rd2);
unsigned int ent2 = AddEntity(&ents, td2, 1);

while(!glfwWindowShouldClose(window))
    {
    // loop
    if(isPressedSingle(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, 1);

    if(isPressedSingle(GLFW_KEY_TAB))
        OutputEntitiesDetails(tds, rds, ents);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
        vec2 cpos = GetCursorPosition(window);
        PlaceBlock(&rds, &tds, &ents, 0, cpos);
        }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    DrawDrawables(rds, tds, drabs, cam);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
