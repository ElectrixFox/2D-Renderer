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
    
// Entity ent = CreateEntity(0, (vec2){0.0f, 0.0f}, "");
// ent.scale = (vec2){50, 50};
// ent.pos = (vec2){-100.0f, 100.0f};


// Entity ent1 = CreateEntityTexture(0, (vec2){0.0f, 0.0f}, "", "res/wood.png");
// ent1.scale = (vec2){50, 50};


float vertices[] = {
    0.5f,  0.5f, 1.0f,      1.0f, 1.0f,
    0.5f, -0.5f, 1.0f,      1.0f, 0.0f,
    -0.5f, -0.5f, 1.0f,     0.0f, 0.0f,
    -0.5f,  0.5f, 1.0f,     0.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

unsigned int vao, vbo, ibo;

vao = CreateVAO();
ibo = CreateIBO(indices, sizeof(indices) / sizeof(indices[0]));
vbo = CreateVBO(vertices, sizeof(vertices) / sizeof(vertices[0]));

unsigned int ss[1] = {3};
VAOLayout layout = CreateVertexLayout(ss, 5, 1);
AddToVertexLayout(&layout, 2);
InitialiseVertexLayout(layout);

unsigned int texture = CreateTexture("res/wood.png"); // create the texture

unsigned int prog = CreateShader("res/texvert.shader", "res/texfrag.shader");

SetUniform1i(prog, "intexture", 0); // set the texture to be used
SetUniformM4(prog, "projection", getM4ID());
SetUniformM4(prog, "model", getM4ID());

// Entity ent1 = { {0.0f, 0.0f}, {1.0f, 1.0f}, (viobject){vao, prog, texture}};

while(!glfwWindowShouldClose(window))
    {
    // loop
    processInput(window);   // do all the input processing here
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer
    // DrawEntity(ent);
    // glActiveTexture(GL_TEXTURE0);
    // DrawEntity(ent1);

    glActiveTexture(GL_TEXTURE0);
    BindTexture(texture);
    BindShader(prog);
    BindVertexArrayObject(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw the object

    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
