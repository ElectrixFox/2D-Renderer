#include <stdio.h>
#include <stdlib.h>

#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>
#include "src/FileHandling.h"

unsigned int createVBO(float vertices[], unsigned int count)
{
unsigned int vbo;
glGenBuffers(1, &vbo);  // generate the buffer
glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind the vbo to type of array buffer to be targetted by buffer data
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * count, vertices, GL_STATIC_DRAW);  // targets the buffer of type GL_ARRAY_BUFFER and then sets its data

return vbo;
}

unsigned int createShader(const char* vertsrc, const char* fragsrc)
{
char errmsg[512];
int success;

unsigned int vertshad;
vertshad = glCreateShader(GL_VERTEX_SHADER);    // creating the shader
glShaderSource(vertshad, 1, &vertsrc, NULL);    // sets the source of the shader
glCompileShader(vertshad);  // compiles the shader

glGetShaderiv(vertshad, GL_COMPILE_STATUS, &success);
if (!success)
    {
    glGetShaderInfoLog(vertshad, 512, NULL, errmsg);
    printf("ERROR: Vertex Shader %s", errmsg);
    }

/*
do error management here
*/

unsigned int fragshad;
fragshad = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragshad, 1, &fragsrc, NULL);
glCompileShader(fragshad);

/*
do error management here
*/
glGetShaderiv(fragshad, GL_COMPILE_STATUS, &success);
if (!success)
    {
    glGetShaderInfoLog(fragshad, 512, NULL, errmsg);
    printf("ERROR: Fragment Shader %s", errmsg);
    }

unsigned int program;   // the program linking both shaders
program = glCreateProgram();
glAttachShader(program, vertshad);
glAttachShader(program, fragshad);
glLinkProgram(program);

glGetProgramiv(program, GL_LINK_STATUS, &success);
if (!success)
    {
    glGetProgramInfoLog(program, 512, NULL, errmsg);
    printf("ERROR: %s", errmsg);
    }
/*
do error checking here
*/

glUseProgram(program);  // actually using the shaders for all future objects

glDeleteShader(vertshad);   // delete the unnecessary shaders
glDeleteShader(fragshad);

return program;
}

void processVertexBuffer(unsigned int vbo)
{
glBindBuffer(GL_VERTEX_ARRAY, vbo); // bind the buffer
glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3 * sizeof(float), (void*)0);  // the first argument is the position to configure (layout (location = 0))
// 3 is for the size of the attribute i.e. vec3 = 3
// GL_INT is the type of data
// 3 * sizeof(float) is the stride or how far apart the next piece of data is
// (void*)0 is just where we start the data to read
glEnableVertexAttribArray(0);   // attribute the data in the 0th buffer to the vertex data
}

unsigned int createIndexArrayBuffer(unsigned int indices[], int count)
{
unsigned int ibo;
glGenBuffers(1, &ibo);  // generating the buffer
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // binding the buffer to an element array buffer
glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);    // writing the indices to it

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // binding the buffer

return ibo;
}

unsigned int createVertexArrayObject(float vertices[], unsigned int vertcount, unsigned int indices[], unsigned int indcount)
{
unsigned int vao;

glGenVertexArrays(1, &vao); // only bind one array and generate the arrays
glBindVertexArray(vao); // bind the array to be used
unsigned int vbo = createVBO(vertices, vertcount);  // create the vbo
unsigned int ibo = createIndexArrayBuffer(indices, indcount);   // create the ibo
processVertexBuffer(vbo);  // process the vbo

return vao;
}

void BindVertexArrayObject(unsigned int vao)
{
glBindVertexArray(vao); // simple bind
}

void BindShader(unsigned int program)
{
glUseProgram(program);  // binds the shader program
}

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
    
const char* vertsrc = ParseShaderSource("res/vertex.shader");
const char* fragsrc = ParseShaderSource("res/fragment.shader");
unsigned int prog = createShader(vertsrc, fragsrc);

float vertices[] = {
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   -0.5f,  0.5f, 0.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

unsigned int vao = createVertexArrayObject(vertices, sizeof(vertices), indices, sizeof(indices));

while(!glfwWindowShouldClose(window))
    {
    // loop
    processInput(window);   // do all the input processing here
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer
    
    glUseProgram(prog);
    BindShader(prog);
    BindVertexArrayObject(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
