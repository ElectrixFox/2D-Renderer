#include "Shader.h"
#include "Texture.h"

// optimise to store the data more compactly
struct viobject // vertex index object
{
unsigned int vao;
unsigned int shader;
unsigned int texture;
unsigned int ibo;
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

void BindVAO(unsigned int vao);

/**
 * @param n n is the number of elements (total including elements of vectors)
 * @note Example: if it is an array of 8 vec3's then n would be 8 * 3 = 24
 */
unsigned int CreateVBO(float vertices[], unsigned int n);

/**
 * creates an ibo.
 * @param n n is the number of elements (total including elements of vectors)
 * @note n is the number of vectors multiplied by their length
 */
unsigned int CreateIBO(unsigned int indices[], unsigned int n);

/**
 * simply creates the vao
 */
unsigned int CreateVAO();

// To-Do: optimise this so the number and buffer length are both stored in one variable
typedef struct VAOLayout
    {
    unsigned int* sizes;
    unsigned int number;
    unsigned int bufflen;
    } VAOLayout;

void BindIBO(unsigned int ibo);

VAOLayout CreateVertexLayout(unsigned int sizes[], unsigned int bufflen, unsigned int n);
void InitialiseVertexLayout(VAOLayout layout);
void AddToVertexLayout(VAOLayout* layout, unsigned int size);

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

Entity CreateEntityA(unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture);
void DrawEntityA(Entity e);

void DrawEntity(Entity e);
