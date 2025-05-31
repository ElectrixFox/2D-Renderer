#include "Shader.h"
#include "Texture.h"
#include "SpriteShapes.h"

struct RenderDetails
    {
    unsigned int* rid;
    unsigned int* vao;
    unsigned int* shader;
    unsigned int* texture;
    unsigned int size;
    };
typedef struct RenderDetails RenderDetails;

/**
 * Initialises a new RenderDetails object
 * 
 * @returns A new initialised RenderDetails object
 */
RenderDetails InitialiseRenderDetails();

/**
 * Returns the index of the render detail
 * 
 * @param rd The render details object
 * @param rid The ID of the details to find
 * 
 * @returns Index of ID in the details object or -1 if not found
 */
int getRenderDetailsIDIndex(RenderDetails rd, unsigned int rid);

/**
 * Adds a render object to the details
 * 
 * @param rd A pointer to the details
 * @param vao The new vao to add
 * @param shader The new shader to add
 * @param texture The new texture to add
 * 
 * @returns The ID of the newly added detail object
 */
unsigned int AddRenderDetail(RenderDetails* rd, unsigned int vao, unsigned int shader, unsigned int texture);

/**
 * Removes a render object from the details
 * 
 * @param rd A pointer to the details
 * @param rid The ID of the object to remove
 */
void RemoveRenderDetail(RenderDetails* rd, unsigned int rid);


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

static unsigned int _CreateRenderable(RenderDetails* rd, unsigned int shape, const char* vsfp, const char* fsfp, const char* texfp);
unsigned int CreateSquareRenderable(RenderDetails* rd);