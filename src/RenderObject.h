#include "Shader.h"

struct viobject // vertex index object
{
unsigned int vao;
unsigned int shader;
};

typedef struct viobject viobject;

struct Entity
{
vec2 pos;
vec2 scale;
viobject rdets;
};

// a renderable needs vertices, a vao and shader
// an object needs position and scale 

typedef struct Entity Entity;

unsigned int createVBO(vec3 vertices[], unsigned int count);

void processVertexBuffer(unsigned int vbo);

unsigned int createIndexArrayBuffer(unsigned int indices[], int count);

unsigned int createVertexArrayObject(vec3 vertices[], unsigned int vertcount, unsigned int indices[], unsigned int indcount);

void BindVertexArrayObject(unsigned int vao);

m4 getEntityModelMatrix4(Entity e);

void UpdateEntity(Entity e);

Entity CreateEntity(unsigned int shape, vec2 position, const char* shader);

void DrawEntity(Entity e);
