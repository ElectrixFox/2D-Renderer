#include "RenderObject.h"

unsigned int createVBO(vec3 vertices[], unsigned int count)
{
unsigned int vbo;
glGenBuffers(1, &vbo);  // generate the buffer
glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind the vbo to type of array buffer to be targetted by buffer data
glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * count, vertices, GL_STATIC_DRAW);  // targets the buffer of type GL_ARRAY_BUFFER and then sets its data

return vbo;
}

unsigned int createVBOFloatVecn(float vertices[], unsigned int count, unsigned int n)
{
unsigned int vbo;
glGenBuffers(1, &vbo);  // generate the buffer
glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind the vbo to type of array buffer to be targetted by buffer data
glBufferData(GL_ARRAY_BUFFER, n * sizeof(float) * count, vertices, GL_STATIC_DRAW);  // targets the buffer of type GL_ARRAY_BUFFER and then sets its data

return vbo;
}

unsigned int CreateVBO(float vertices[], unsigned int n)
{
unsigned int vbo;
glGenBuffers(1, &vbo);  // generate the buffer
glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind the vbo to type of array buffer to be targetted by buffer data
glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, vertices, GL_STATIC_DRAW);  // targets the buffer of type GL_ARRAY_BUFFER and then sets its data

return vbo;
}

unsigned int CreateIBO(unsigned int indices[], unsigned int n)
{
unsigned int ibo;
glGenBuffers(1, &ibo);  // generating the buffer
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // binding the buffer to an element array buffer
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * n, indices, GL_STATIC_DRAW);    // writing the indices to it

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // binding the buffer

return ibo;
}

unsigned int CreateVAO()
{
unsigned int vao;

glGenVertexArrays(1, &vao); // only bind one array and generate the arrays
glBindVertexArray(vao); // bind the array to be used

return vao;
}

void AddToVertexLayout(VAOLayout* layout, unsigned int size)
{
void* nptr = malloc(sizeof(unsigned int*) * (*layout).number); // allocating the new memory
nptr = realloc((*layout).sizes, sizeof(unsigned int) * ((*layout).number + 1));  // making the array bigger
(*layout).sizes = nptr;    // setting the old array to the new bigger one
(*layout).sizes[(*layout).number] = size; // setting the new size element
(*layout).number++;    // increase the number of elements in the whole layout
}

VAOLayout CreateVertexLayout(unsigned int sizes[], unsigned int bufflen, unsigned int n)
{
VAOLayout layout;
layout.sizes = (unsigned int*)malloc(n * sizeof(unsigned int)); // allocating the size
for(int i = 0; i < n; i++)
    {
    layout.sizes[i] = sizes[i];
    }
layout.bufflen = bufflen;
layout.number = n;

return layout;
}

void InitialiseVertexLayout(VAOLayout layout)
{
unsigned int stride = 0;
for(int i = 0; i < layout.number; i++)
    {
    printf("\nglVertexAttribPointer(%d, %d, GL_FLOAT, GL_FALSE, %d * sizeof(float), (void*)(%d * sizeof(float)))", i, layout.sizes[i], layout.bufflen, stride);
    glVertexAttribPointer(i, layout.sizes[i], GL_FLOAT, GL_FALSE, layout.bufflen * sizeof(float), (void*)(stride * sizeof(float))); // adding the pointer
    glEnableVertexAttribArray(i);   // attributing the data.
    stride += layout.sizes[i];
    }
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

void processVertexBufferFloatVecn(unsigned int vbo, unsigned int count, unsigned int n)
{
glBindBuffer(GL_VERTEX_ARRAY, vbo);
glVertexAttribPointer(0, 3, GL_FLOAT, 0, n * count * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 2, GL_FLOAT, 0, n * count * sizeof(float), (void*)(sizeof(vec3)));
glEnableVertexAttribArray(1);
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

unsigned int createVertexArrayObjectFloatVecn(float vertices[], unsigned int vertcount, unsigned int indices[], unsigned int indcount, unsigned int n)
{
unsigned int vao;

glGenVertexArrays(1, &vao); // only bind one array and generate the arrays
glBindVertexArray(vao); // bind the array to be used
unsigned int vbo = createVBOFloatVecn(vertices, vertcount, n);  // create the vbo
unsigned int ibo = createIndexArrayBuffer(indices, indcount);   // create the ibo
processVertexBufferFloatVecn(vbo, vertcount, n);  // process the vbo
return vao;
}

void BindVertexArrayObject(unsigned int vao)
{
glBindVertexArray(vao); // simple bind
}

void BindVAO(unsigned int vao)
{
glBindVertexArray(vao); // simple bind
}

void BindIBO(unsigned int ibo)
{
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // binding the buffer
}

m4 getEntityModelMatrix4(Entity e)
{
/*
return mat3Tomat4((mat3){
    (vec3){e.scale.x, 0.0f, e.pos.x},
    (vec3){0.0f, e.scale.y, e.pos.y},
    (vec3){0.0f, 0.0f, 1.0f}
});
*/
return (m4){
        e.scale.x, 0.0f, 0.0f, e.pos.x,
        0.0f, e.scale.y, 0.0f, e.pos.y,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
};
}

void UpdateEntity(Entity e)
{
const unsigned int prog = e.rdets.shader;  // constant just for safety
BindShader(prog);
SetUniformM4(prog, "model", getEntityModelMatrix4(e)); // getting and setting the model matrix
}

Entity CreateEntity(unsigned int shape, vec2 position, const char* shader)
{
// do something here to determine shape
vec2 scale = {1.0f, 1.0f}; // default scale

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
const char* vertsrc = ParseShaderSource("res/vertex.shader");
const char* fragsrc = ParseShaderSource("res/fragment.shader");
unsigned int prog = createShader(vertsrc, fragsrc);

BindShader(prog);
SetUniformM4(prog, "projection", getProjection(1020, 960)); // getting and setting the projection

mat3 modelmat = {
    (vec3){scale.x, 0.0f, position.x},
    (vec3){0.0f, scale.y, position.y},
    (vec3){0.0f, 0.0f, 1.0f}
};

SetUniformM4(prog, "model", mat3Tomat4(modelmat)); // getting and setting the model matrix

unsigned int vao = createVertexArrayObject(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices));
return (Entity){ position, scale, (viobject){vao, prog, 0, 0}};
}

Entity CreateEntityTexture(unsigned int shape, vec2 position, const char* shader, const char* texture)
{
// do something here to determine shape
vec2 scale = {1.0f, 1.0f}; // default scale

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

// ScaleObject(vertices, (vec2){2.0f, 2.0f}, 4);
const char* vertsrc = ParseShaderSource("res/texvert.shader");
const char* fragsrc = ParseShaderSource("res/texfrag.shader");
unsigned int prog = createShader(vertsrc, fragsrc);

BindShader(prog);
SetUniformM4(prog, "projection", getProjection(1020, 960)); // getting and setting the projection

mat3 modelmat = {
    (vec3){scale.x, 0.0f, position.x},
    (vec3){0.0f, scale.y, position.y},
    (vec3){0.0f, 0.0f, 1.0f}
};

SetUniformM4(prog, "model", mat3Tomat4(modelmat)); // getting and setting the model matrix

unsigned int vao, vbo, ibo;
glGenVertexArrays(1, &vao);
glGenBuffers(1, &ibo);
glBindVertexArray(vao);

vbo = createVBOFloatVecn(vertices, sizeof(vertices) / sizeof(vertices[0]), 5);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);


// unsigned int vao = createVertexArrayObjectFloatVecn(vertices, 4, indices, 6, 5);
unsigned int tex = CreateTexture(texture); // create the texture
// glVertexAttribPointer(1, 2, GL_FLOAT, 0, 5 * sizeof(float), (void*)(sizeof(vec3))); // setting the texture coordinates
// glEnableVertexAttribArray(1);   // attribute the data in the 1th buffer to the vertex data

glActiveTexture(GL_TEXTURE0);   // activate the texture

BindTexture(tex); // bind the texture
SetUniform1i(prog, "intexture", 1); // set the texture uniform to 0
return (Entity){ position, scale, (viobject){vao, prog}};
}

void DrawEntity(Entity e)
{
BindShader(e.rdets.shader);
UpdateEntity(e); // update the entity
BindVertexArrayObject(e.rdets.vao);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Entity CreateEntityA(unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture)
{
unsigned int vao, vbo, ibo, prog;
unsigned int tex = 0;
vec2 scale = {1.0f, 1.0f};
// vertices = GetShapeVertices(shape);
// indices = GetShapeIndices(shape);


float vertices[] = {
    1.0f,  1.0f, 1.0f,      1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,      1.0f, 0.0f,
    -1.0f, -1.0f, 1.0f,     0.0f, 0.0f,
    -1.0f,  1.0f, 1.0f,     0.0f, 1.0f
};
    
/*
float vertices[] = {
    1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f
};*/

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

m4 model = (m4){
        scale.x, 0.0f, 0.0f, position.x,
        0.0f, scale.y, 0.0f, position.y,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
};


vao = CreateVAO();  // creating the vao
ibo = CreateIBO(indices, sizeof(indices) / sizeof(indices[0])); // creating the ibo
vbo = CreateVBO(vertices, sizeof(vertices) / sizeof(vertices[0]));  // creating the vbo

unsigned int ilay[1] = {3};
VAOLayout layout = CreateVertexLayout(ilay, 5, 1);  // setting up the layout
AddToVertexLayout(&layout, 2);  // adding the texture coords to the layout
InitialiseVertexLayout(layout); // initialising the layout to be used

prog = CreateShader(vshader, fshader);

if(texture != NULL)
    {
    tex = CreateTexture(texture);
    SetUniform1i(prog, "intexture", 0); // set the texture to be used (the 0th active texture)
    }


SetUniformM4(prog, "projection", getProjection(1020, 960));
SetUniformM4(prog, "model", model);

return (Entity){position, scale, {vao, prog, tex, ibo}};
}

void DrawEntityA(Entity e)
{
UpdateEntity(e);
if (e.rdets.texture != 0)
    {
    glActiveTexture(GL_TEXTURE0);
    BindTexture(e.rdets.texture);
    }

BindShader(e.rdets.shader);
BindVAO(e.rdets.vao);
//  the 6 should be changed to the number of indices
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}