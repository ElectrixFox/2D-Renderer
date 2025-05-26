#include <stdio.h>
#include <stdlib.h>

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

vec2 GetCursorPosition(GLFWwindow* window)
{
double x, y;
int wid, hig;
glfwGetCursorPos(window, &x, &y);
glfwGetWindowSize(window, &wid, &hig);
vec2 point = GetMousePositionRelative((vec2){x, y}, wid, hig);

return point;
}

int main()
{
unsigned int width = 1020;
unsigned int height = 960;
glfwInit();
// (0, 0) is the top left
GLFWwindow* window = glfwCreateWindow(width, height, "Title", 0, 0); // creates the window of size width x height

glfwMakeContextCurrent(window); // sets the context of the window
glViewport(0, 0, width, height);

glewInit();

Entity ent1 = CreateEntity(0, (vec2){0.0f, 0.0f}, "res/texvert.shader", "res/texfrag.shader", "res/wood.png");
ent1.scale = (vec2){25.0f, 25.0f};
ent1.pos = (vec2){535.0f, 430.0f};
SetUniform4f(ent1.rdets.shader, "colour", (vec4){0.75f, 0.0f, 0.0f, 1.0f});


Entity ent2 = CreateEntity(0, (vec2){0.0f, 0.0f}, "res/vertex.shader", "res/fragment.shader", NULL);
ent2.scale = (vec2){25.0f, 25.0f};
ent2.pos = (vec2){485.0f, 430.0f};
SetUniform4f(ent2.rdets.shader, "colour", (vec4){0.0f, 0.75f, 0.0f, 1.0f});

unsigned int ids[] = {ent1.id, ent2.id};
unsigned int shads[] = {ent1.rdets.shader, ent2.rdets.shader};
unsigned int textures[] = {ent1.rdets.texture, ent2.rdets.texture};
unsigned int vaos[] = {ent1.rdets.vao, ent2.rdets.vao};
vec2 poses[] = {ent1.pos, ent2.pos};
vec2 scales[] = {ent1.scale, ent2.scale};
unsigned int size = 2;

unsigned int* pressables = (unsigned int*)malloc(sizeof(unsigned int) * 1);
unsigned int n = 0;

UpdateEntities(shads, poses, scales, size);
AddPressable(pressables, ids[0], &n);


while(!glfwWindowShouldClose(window))
    {
    // loop
    processInput(window);   // do all the input processing here
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
        vec2 cpos = GetCursorPosition(window);
        CheckPressed(poses, scales, cpos, ids[0]);
        }
    UpdateEntities(shads, poses, scales, size);
    DrawEntities(textures, shads, vaos, size);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
