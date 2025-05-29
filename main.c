#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>
#include "src/Entity.h"
#include "src/PressableObject.h"

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

void MovePointer(vec2* pos, unsigned int dir)
{
switch (dir)
    {
    case 0: // move up
        pos->y += 5;
        break;
    case 1: // move right
        pos->x += 5;
        break;
    case 2: // move down
        pos->y -= 5;
        break;
    case 3: // move left
        pos->x -= 5;
        break;
    default:
        break;
    }
}

unsigned int ckey = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
if(action == GLFW_PRESS)
    {
    ckey = key;
    }
if(action == GLFW_REPEAT)
    {
    ckey = key;
    }
if(action == GLFW_RELEASE)
    {
    ckey = 0;
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

void OutputEntitiesDetails(Entities es)
{
printf("\nSize: %d", es.size);
printf("\n%10s\t%s\t%13s\t\t%13s %10s %8s\t", "ID", "Position", "Scale", "Shader", "Texture", "VAO");
for (int i = 0; i < es.size; i++)
    {
    printf("\n%10d\t(%.2f, %.2f)\t(%.2f, %.2f)\t%10d %10d %10d\t",
        es.ids[i],
        es.positions[i].x, es.positions[i].y,
        es.scales[i].x, es.scales[i].y,
        es.rdets.shaders[i], es.rdets.textures[i], es.rdets.vaos[i]);
    }
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

Entities es = InitialiseEntities(); // initialising the entities list and allocating memory

unsigned int ent1 = CreateEntity(&es, SQUARE, (vec2){535.0f, 430.0f}, "res/texvert.shader", "res/texfrag.shader", "res/wood.png");
SetEntityScale(es, ent1, (vec2){25.0f, 25.0f});
/*unsigned int ent2 = CreateEntity(&es, SQUARE, (vec2){485.0f, 430.0f}, "res/vertex.shader", "res/fragment.shader", NULL);
SetEntityScale(es, ent2, (vec2){25.0f, 25.0f});
SetEntityColour(es, ent2, (vec4){0.75f, 0.0f, 0.0f, 1.0f});
*/
// setting up the block bar
// unsigned int bar = CreateEntityFromSpriteSheet(&es, SQUARE, (vec2){(float)(width - 25), (float)(height - 50)}, "res/sprites/movable_spritesheet.png", 1, 2);
// SetEntityScaleFactor(es, bar, 25.0f);

/*
unsigned int* pressables = (unsigned int*)malloc(sizeof(unsigned int) * 1);
unsigned int n = 0;

AddPressable(pressables, es.ids[0], &n);
*/
/*
unsigned int pent = CreateEntity(&es, SQUARE, (vec2){0.0f, 0.0f}, "res/vertex.shader", "res/fragment.shader", NULL);
SetEntityScale(es, pent, (vec2){5.0f, 5.0f});
SetEntityColour(es, pent, (vec4){0.0f, 0.0f, 0.0f, 1.0f});
*/
UpdateEntities(es);

glfwSetKeyCallback(window, key_callback);
while(!glfwWindowShouldClose(window))
    {
    // loop
    processInput(window);   // do all the input processing here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    /*
    if(ckey == GLFW_KEY_W)
        {
        vec2 posi = GetEntityPosition(es, pent);
        MovePointer(&posi, 0);
        SetEntityPosition(es, pent, posi);
        ckey = 0;
        }
    else if(ckey == GLFW_KEY_D)
        {
        vec2 posi = GetEntityPosition(es, pent);
        MovePointer(&posi, 1);
        SetEntityPosition(es, pent, posi);
        ckey = 0;
        }
    else if(ckey == GLFW_KEY_S)
        {
        vec2 posi = GetEntityPosition(es, pent);
        MovePointer(&posi, 2);
        SetEntityPosition(es, pent, posi);
        ckey = 0;
        }
    else if(ckey == GLFW_KEY_A)
        {
        vec2 posi = GetEntityPosition(es, pent);
        MovePointer(&posi, 3);
        SetEntityPosition(es, pent, posi);
        ckey = 0;
        }
    else if(ckey == GLFW_KEY_ENTER)
        {
        vec2 posi = GetEntityPosition(es, pent);
        vec2 scali = GetEntityScale(es, pent);
        unsigned int nent = CreateEntity(&es, 0, posi, "res/vertex.shader", "res/fragment.shader", NULL);
        SetEntityScale(es, nent, (vec2){25.0f, 25.0f});
        SetEntityColour(es, nent, (vec4){1.0f, 0.0f, 0.0f, 1.0f});
        ckey = 0;
        }
    if(ckey == GLFW_KEY_Z && ckey & GLFW_MOD_CONTROL)
        {
        es.size = es.size - 1;
        ckey = 0;
        }
    */

    if(ckey == GLFW_KEY_TAB)
        {
        OutputEntitiesDetails(es);
        ckey = 0;
        }
    /*
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
        vec2 cpos = GetCursorPosition(window);

        if(CheckPressed(es.positions, es.scales, cpos, pent))
            {
            // printf("\nPressed");
            }

            {   // moving the pointer
            vec2 posi = GetEntityPosition(es, pent);
            vec2 nposi = {50 * round(cpos.x / 50), 50 * round(cpos.y / 50)};
            SetEntityPosition(es, pent, nposi);
            }
        }
    // float tim = sin(2 * glfwGetTime());
    SetEntityColour(es, pent, (vec4){0.0f, 0.0f, 0.0f, 1.0f * 1});
    */

    UpdateEntities(es);
    DrawEntities(es);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
