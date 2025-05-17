#include "Shader.h"
#include "MathsOperations.h"

struct viobject // vertex index object
{
unsigned int vao;
unsigned int shader;
};

typedef struct viobject viobject;

struct robj
{
vec2 pos;
vec2 scale;
viobject rdets;
};

typedef struct robj robj;

unsigned int createVBO(vec3 vertices[], unsigned int count);

void processVertexBuffer(unsigned int vbo);

unsigned int createIndexArrayBuffer(unsigned int indices[], int count);

unsigned int createVertexArrayObject(vec3 vertices[], unsigned int vertcount, unsigned int indices[], unsigned int indcount);

void BindVertexArrayObject(unsigned int vao);


void CreateObject();
