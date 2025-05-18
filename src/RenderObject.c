#include "RenderObject.h"

unsigned int createVBO(vec3 vertices[], unsigned int count)
{
unsigned int vbo;
glGenBuffers(1, &vbo);  // generate the buffer
glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind the vbo to type of array buffer to be targetted by buffer data
glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * count, vertices, GL_STATIC_DRAW);  // targets the buffer of type GL_ARRAY_BUFFER and then sets its data

return vbo;
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

unsigned int createVertexArrayObject(vec3 vertices[], unsigned int vertcount, unsigned int indices[], unsigned int indcount)
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


Entity CreateEntity(unsigned int shape, vec2 position, const char* shader)
{
// do something here to determine shape

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

ScaleObject(vertices, (vec2){2.0f, 2.0f}, 4);
/*
ScaleObject(vertices, (vec2){1 / 1020.0f, 1 / 960.0f}, 4);
printf("\n%f %f %f", vertices[0].x, vertices[0].y, vertices[0].z);
printf("\n%f %f %f", vertices[1].x, vertices[1].y, vertices[1].z);
printf("\n%f %f %f", vertices[2].x, vertices[2].y, vertices[2].z);
printf("\n%f %f %f", vertices[3].x, vertices[3].y, vertices[3].z);
ScaleObject(vertices, (vec2){100.0f, 100.0f}, sizeof(vertices) / sizeof(vertices[0]));
*/
const char* vertsrc = ParseShaderSource("res/vertex.shader");
const char* fragsrc = ParseShaderSource("res/fragment.shader");
unsigned int prog = createShader(vertsrc, fragsrc);
SetUniformM4(prog, "projection", getProjection(1020, 960));

unsigned int vao = createVertexArrayObject(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices));
return (Entity){ {position.x, position.y}, {1.0f, 1.0f}, {vao, prog}};
}

void DrawEntity(Entity e)
{
BindShader(e.rdets.shader);
BindVertexArrayObject(e.rdets.vao);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}