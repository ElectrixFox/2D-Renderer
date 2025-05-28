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
GLFWwindow* window = glfwCreateWindow(width, height, "Title", 0, 0); // creates the window of size width x height

glfwMakeContextCurrent(window); // sets the context of the window
glViewport(0, 0, width, height);

glewInit();

Entities es;
es.size = 0;
es.ids = malloc(sizeof(unsigned int) * 1);
es.positions = malloc(sizeof(vec2) * 1);
es.scales = malloc(sizeof(vec2) * 1);
es.rdets.shaders = malloc(sizeof(unsigned int) * 1);
es.rdets.textures = malloc(sizeof(unsigned int) * 1);
es.rdets.vaos = malloc(sizeof(unsigned int) * 1);


CreateEntity(&es, 0, (vec2){535.0f, 430.0f}, "res/texvert.shader", "res/texfrag.shader", "res/wood.png");
CreateEntity(&es, 0, (vec2){485.0f, 430.0f}, "res/vertex.shader", "res/fragment.shader", NULL);
printf("\n%d", es.size);
SetEntityScale(es, es.ids[0], (vec2){25.0f, 25.0f});
SetEntityScale(es, es.ids[1], (vec2){25.0f, 25.0f});
SetEntityColour(es, es.ids[1], (vec4){0.75f, 0.0f, 0.0f, 1.0f});

unsigned int* pressables = (unsigned int*)malloc(sizeof(unsigned int) * 1);
unsigned int n = 0;

UpdateEntities(es);
AddPressable(pressables, es.ids[0], &n);


while(!glfwWindowShouldClose(window))
    {
    // loop
    processInput(window);   // do all the input processing here
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
        vec2 cpos = GetCursorPosition(window);
        CheckPressed(es.positions, es.scales, cpos, es.ids[0]);
        }
    UpdateEntities(es);
    DrawEntities(es);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
