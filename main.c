#include <stdio.h>
#include <stdlib.h>
#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>

const char* vss = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fss = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

unsigned int createVBO(float vertices[])
{
unsigned int vbo;
glGenBuffers(1, &vbo);  // generate the buffer
glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind the vbo to type of array buffer to be targetted by buffer data
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // targets the buffer of type GL_ARRAY_BUFFER and then sets its data
}

unsigned int createShader(const char* vertsrc, const char* fragsrc)
{
unsigned int vertshad;
vertshad = glCreateShader(GL_VERTEX_SHADER);    // creating the shader
glShaderSource(vertshad, 1, &vertsrc, NULL);    // sets the source of the shader
glCompileShader(vertshad);  // compiles the shader

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

unsigned int program;   // the program linking both shaders
program = glCreateProgram();
glAttachShader(program, vertshad);
glAttachShader(program, fragshad);

/*
do error checking here
*/

glUseProgram(program);  // actually using the shaders for all future objects

glDeleteShader(vertshad);   // delete the unnecessary shaders
glDeleteShader(fragshad);
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

unsigned int createVertexArray(float vertices[], unsigned int vbo)
{
unsigned int vao;
glGenVertexArrays(1, &vao); // only bind one array and generate the arrays

glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind the buffer
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // copy the buffer data into the vertex array

glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3 * sizeof(float), (void*)0);  // set the vertex pointer
glEnableVertexAttribArray(0);   // set the attributes
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

GLFWwindow* window = glfwCreateWindow(100, 100, "Title", 0, 0); // creates the window of size 100x100

glfwMakeContextCurrent(window); // sets the context of the window
glViewport(0, 0, 100, 100);

glewInit();

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

unsigned int vbo = createVBO(vertices);
unsigned int prog = createShader(vss, fss);
unsigned int vao = createVertexArray(vertices, vbo);

while(!glfwWindowShouldClose(window))
    {
    // loop
    processInput(window);   // do all the input processing here
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}