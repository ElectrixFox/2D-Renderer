#include <stdio.h>
#include <stdlib.h>

#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>
#include "src/RenderObject.h"
#include "src/Texture.h"

void processInput(GLFWwindow* window)
{
if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // if the escape key is pressed close the window
    {
    glfwSetWindowShouldClose(window, 1);
    }
}

int main()
{
glfwInit();
GLFWwindow* window = glfwCreateWindow(1020, 960, "Title", 0, 0); // creates the window of size 100x100

glfwMakeContextCurrent(window); // sets the context of the window
glViewport(0, 0, 1020, 960);

glewInit();
/*
Entity ent1 = CreateEntityA(0, (vec2){0.0f, 0.0f}, "res/texvert.shader", "res/texfrag.shader", "res/wood.png");
ent1.scale = (vec2){100.0f, 100.0f};
*/
// Entity ent1 = CreateEntityA(0, (vec2){0.0f, 0.0f}, "res/vertex.shader", "res/fragment.shader", NULL);
// ent1.scale = (vec2){100.0f, 100.0f};
// SetUniform4f(ent1.rdets.shader, "colour", (vec4){0.75f, 0.0f, 0.0f, 1.0f});

Entity ent2 = CreateEntityA(0, (vec2){0.0f, 0.0f}, "res/vertex.shader", "res/fragment.shader", NULL);
ent2.scale = (vec2){100.0f, 100.0f};
ent2.pos = (vec2){1.0f, 1.0f};
SetUniform4f(ent2.rdets.shader, "colour", (vec4){0.0f, 0.75f, 0.0f, 1.0f});

while(!glfwWindowShouldClose(window))
    {
    // loop
    processInput(window);   // do all the input processing here
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    // DrawEntityA(ent1);
    
    DrawEntityA(ent2);

    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
