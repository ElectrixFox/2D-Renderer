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

#include "src/Input.h"

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

/*
void OutputEntitiesDetails(Entities es)
{
printf("\nSize: %d", es.size);
printf("\n%10s\t%s\t%13s\t\t%13s %10s %8s\t", "ID", "Position", "Scale", "Shader", "Texture", "VAO");
for (int i = 0; i < es.size; i++)
    {
    printf("\n%10d\t(%.2f, %.2f)\t(%.2f, %.2f)\t%10d %10d %10d\t",
        es.eid[i],
        es.positions[i].x, es.positions[i].y,
        es.scales[i].x, es.scales[i].y,
        es.rdets.shaders[i], es.rdets.textures[i], es.rdets.vaos[i]);
    }
}
*/

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

/*
void PlaceNew(Entities es, unsigned int pid, unsigned int sprite)
{
vec2 posi = GetEntityPosition(es, pid);

//  To-Do: could check here if there is already an entity with the position and then cancel the action if so
unsigned int nent = CreateEntityFromSpriteSheet(&es, SQUARE, posi, "res/sprites/movable_spritesheet.png", sprite, 2);
SetEntityScale(es, nent, (vec2){25.0f, 25.0f});
SetEntityColour(es, nent, (vec4){1.0f, 0.0f, 0.0f, 1.0f});
}
*/

/** Outline for sprite selection:
 * - Set all the object bar as pressable
 * - Return the eid of the entity pressed when it is pressed
 * - Use the eid to determine what texture and sprite the entity has
 * - Return the sheet and the sprite information to be used
 */

void ApplyModel(RenderDetails rds, TransformationDetails tds, unsigned int rid, unsigned int tid)
{
int tindex = getTransformationIDIndex(tds, tid);
int rindex = getRenderDetailsIDIndex(rds, rid);

m4 matr = getTransformModelMatrix(tds, tid);
SetUniformM4(rds.shader[rindex], "model", matr);
}

int main()
{
unsigned int width = 1020;
unsigned int height = 960;

glfwInit();
GLFWwindow* window = glfwCreateWindow(width, height, "Title", 0, 0); // creates the window of size width x height

glfwMakeContextCurrent(window); // sets the context of the window
glViewport(0, 0, width, height);

glewInit();
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

InitialiseInput(window);

RenderDetails rds = InitialiseRenderDetails();
TransformationDetails tds = InitialiseTransformationDetails();
Entities ents = InitialiseEntities(); // initialising the entities list and allocating memory


unsigned int rd1 = CreatePlainSquareRenderable(&rds);
// unsigned int rd1 = CreateSquareRenderable(&rds);
unsigned int td1 = AddTransformation(&tds, (vec2){520.0f, 520.0f}, (vec2){100.0f, 100.0f});

int rind = getRenderDetailsIDIndex(rds, rd1);
SetUniform4f(rds.shader[rind], "colour", (vec4){1.0f, 0.0f, 0.0f, 1.0f});

unsigned int ent1 = CreateEntity(&ents, rd1, td1);

/*
unsigned int ent1 = CreateEntity(&es, SQUARE, (vec2){535.0f, 430.0f}, "res/texvert.shader", "res/texfrag.shader", "res/wood.png");
SetEntityScale(es, ent1, (vec2){25.0f, 25.0f});
unsigned int ent2 = CreateEntity(&es, SQUARE, (vec2){485.0f, 430.0f}, "res/vertex.shader", "res/fragment.shader", NULL);
SetEntityScale(es, ent2, (vec2){25.0f, 25.0f});
SetEntityColour(es, ent2, (vec4){0.75f, 0.0f, 0.0f, 1.0f});

// setting up the block bar
unsigned int bar1 = CreateEntityFromSpriteSheet(&es, SQUARE, (vec2){(float)(width - 25), (float)(height - 50)}, "res/sprites/movable_spritesheet.png", 1, 2);
unsigned int bar2 = CreateEntityFromSpriteSheet(&es, SQUARE, (vec2){(float)(width - 25), (float)(height - 100)}, "res/sprites/movable_spritesheet.png", 2, 2);

SetEntityScaleFactor(es, bar1, 25.0f);
SetEntityScaleFactor(es, bar2, 25.0f);


unsigned int pent = CreateEntity(&es, SQUARE, (vec2){0.0f, 0.0f}, "res/vertex.shader", "res/fragment.shader", NULL);
SetEntityScale(es, pent, (vec2){5.0f, 5.0f});
SetEntityColour(es, pent, (vec4){0.0f, 0.0f, 0.0f, 1.0f});

UpdateEntities(es);
*/

while(!glfwWindowShouldClose(window))
    {
    // loop
    if(isPressedSingle(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, 1);

    if(isPressedSingle(GLFW_KEY_TAB))
        OutputEntitiesDetails(tds, rds, ents);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    ApplyModel(rds, tds, rd1, td1);
    DrawRenderable(rds, rd1);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
