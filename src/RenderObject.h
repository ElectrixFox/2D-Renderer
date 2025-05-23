#include "Shader.h"
#include "Texture.h"

struct viobject // vertex index object
{
unsigned int vao;
unsigned int shader;
unsigned int texture;
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
unsigned int createVBOVecn(float vertices[], unsigned int count, unsigned int n);

/*@param n is the number of elements (total including elements of vectors).
 *@note Example: if it is an array of 8 vec3's then n would be 8 * 3 = 24.
 */
unsigned int CreateVBO(float vertices[], unsigned int n);

void processVertexBuffer(unsigned int vbo);
void processVertexBufferVecn(unsigned int vbo, unsigned int count, unsigned int n);

unsigned int createIndexArrayBuffer(unsigned int indices[], int count);

unsigned int createVertexArrayObject(vec3 vertices[], unsigned int vertcount, unsigned int indices[], unsigned int indcount);
unsigned int createVertexArrayObjectVecn(float vertices[], unsigned int vertcount, unsigned int indices[], unsigned int indcount, unsigned int n);

void BindVertexArrayObject(unsigned int vao);

m4 getEntityModelMatrix4(Entity e);

void UpdateEntity(Entity e);

Entity CreateEntity(unsigned int shape, vec2 position, const char* shader);

Entity CreateEntityTexture(unsigned int shape, vec2 position, const char* shader, const char* texture);

void DrawEntity(Entity e);
