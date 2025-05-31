#include "Shader.h"
#include "Texture.h"

struct RenderDetails
    {
    unsigned int* rid;
    unsigned int* vao;
    unsigned int* shader;
    unsigned int* texture;
    };
typedef struct RenderDetails RenderDetails;


// optimise to store the data more compactly
struct viobject // vertex index object
{
unsigned int* vaos;
unsigned int* shaders;
unsigned int* textures;
};

typedef struct viobject viobject;

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
