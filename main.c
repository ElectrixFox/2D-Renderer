#include <stdio.h>
#include <stdlib.h>

#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>
#include "src/Entity.h"

void processInput(GLFWwindow* window)
{
if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // if the escape key is pressed close the window
    {
    glfwSetWindowShouldClose(window, 1);
    }
if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)  // if the escape key is pressed close the window
    {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    printf("\n(%.2f, %.2f)", x, y);
    }
}

Entity MakeGrid()
{
Entity grid = CreateEntity(0, (vec2){0.0f, 0.0f}, "res/gridvert.shader", "res/gridfrag.shader", "res/grid_tile.png");
BindTexture(grid.rdets.texture);

grid.scale = (vec2){1020.0f, 960.0f};

return grid;
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
/*
Entity ent1 = CreateEntity(0, (vec2){0.0f, 0.0f}, "res/texvert.shader", "res/texfrag.shader", "res/wood.png");
ent1.scale = (vec2){100.0f, 100.0f};
ent1.pos = (vec2){1020.0f, 960.0f};
SetUniform4f(ent1.rdets.shader, "colour", (vec4){0.75f, 0.0f, 0.0f, 1.0f});
*/

Entity ent2 = CreateEntity(0, (vec2){0.0f, 0.0f}, "res/vertex.shader", "res/fragment.shader", NULL);
ent2.scale = (vec2){100.0f, 100.0f};
ent2.pos = (vec2){520.0f, 430.0f};
SetUniform4f(ent2.rdets.shader, "colour", (vec4){0.0f, 0.75f, 0.0f, 1.0f});

Entity grid = MakeGrid();

while(!glfwWindowShouldClose(window))
    {
    // loop
    processInput(window);   // do all the input processing here
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    // DrawEntity(ent1);
    DrawEntity(grid);
    
    DrawEntity(ent2);

    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
