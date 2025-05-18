#include <stdio.h>
#include <stdlib.h>

#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>
#include "src/RenderObject.h"

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
const char* vertsrc = ParseShaderSource("res/vertex.shader");
const char* fragsrc = ParseShaderSource("res/fragment.shader");
unsigned int prog = createShader(vertsrc, fragsrc);

vec3 vertices[] = {
    {0.5f,  0.5f, 1.0f},
    {0.5f, -0.5f, 1.0f},
    {-0.5f, -0.5f, 1.0f},
    {-0.5f,  0.5f, 1.0f}
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

vec2 trans = { 1.0f, 1.0f };
TransformObject(vertices, trans, sizeof(vertices) / sizeof(vec3));
unsigned int vao = createVertexArrayObject(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices));
*/

Entity ent = CreateEntity(0, (vec2){0.0f, 0.0f}, "");

while(!glfwWindowShouldClose(window))
    {
    // loop
    processInput(window);   // do all the input processing here
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer
    
    DrawEntity(ent);
    /*
    BindShader(prog);
    BindVertexArrayObject(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    */

    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
