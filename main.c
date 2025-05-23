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
glGenVertexArrays(1, &vao);
// glGenBuffers(1, &vbo);
glGenBuffers(1, &ibo);

glBindVertexArray(vao);

vbo = CreateVBO(vertices, sizeof(vertices) / sizeof(vertices[0]));
// glBindBuffer(GL_ARRAY_BUFFER, vbo);
// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);

unsigned int texture = CreateTexture("res/wood.png"); // create the texture

/*
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

int width, height, nrChannels;
stbi_set_flip_vertically_on_load(1); // flip the texture vertically
unsigned char* data = stbi_load("res/wood.png", &width, &height, &nrChannels, 0);
if (data)
    {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    }
else
    {
    printf("Failed to load texture\n");
    }
stbi_image_free(data);
*/
const char* vss = ParseShaderSource("res/texvert.shader");
const char* fss = ParseShaderSource("res/texfrag.shader");

m4 id = (m4){
    {1.0f, 0.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f, 0.0f,
     0.0f, 0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 0.0f, 1.0f}
};

unsigned int prog = createShader(vss, fss);
SetUniform1i(prog, "intexture", 0); // set the texture to be used
SetUniformM4(prog, "projection", id);
SetUniformM4(prog, "model", id);

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
    glBindTexture(GL_TEXTURE_2D, texture);

    BindShader(prog);
    BindVertexArrayObject(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw the object

    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
