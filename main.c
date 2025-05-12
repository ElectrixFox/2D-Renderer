#include <stdio.h>
#include <stdlib.h>
#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>


int main()
{
glfwInit();

GLFWwindow* window = glfwCreateWindow(100, 100, "Title", 0, 0); // creates the window of size 100x100

glfwMakeContextCurrent(window); // sets the context of the window

glewInit();

while(!glfwWindowShouldClose(window))
    {
    // loop
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}