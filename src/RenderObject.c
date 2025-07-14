#include "RenderObject.h"

typedef struct
    {
    char txfps[32][64];  // array of texture file paths
    Array tex[32];  // array of textures
    } TEXTURE_CONTAINER;
static TEXTURE_CONTAINER tex_cont;

typedef struct
    {
    char vsfps[32][64];  // array of vertex shader file paths
    char fsfps[32][64];  // array of fragment shader file paths
    Array progs[32];    // array of shaders
    } SHADER_CONTAINER;
static SHADER_CONTAINER shad_cont;

static int shaderExists(const char* vsfp, const char* fsfp)
{
int check = 0;

int nfps = shad_cont.progs->size;
    
for (int i = 0; i < nfps; i++)  // loop through all of the file paths
    if(strcmp(shad_cont.vsfps[i], vsfp) == 0) // if the file path is already in the array
        return 1;

// ASSUMPTION: If the vertex shader is unique then the fragment one is too
strcpy(shad_cont.vsfps[nfps], vsfp);    // copy the new file path into the filepaths array
strcpy(shad_cont.fsfps[nfps], fsfp);    // add the fragment shader too as then it keeps them together

return 0;
}

static unsigned int getShader(const char* vsfp, const char* fsfp)
{
int check = 0;

int nfps = shad_cont.progs->size;
    
for (int i = 0; i < nfps; i++)  // loop through all of the file paths
    if(strcmp(shad_cont.vsfps[i], vsfp) == 0) // if the file path is already in the array
        return shad_cont.progs->data[i];
return 0;
}

RenderDetails InitialiseRenderDetails()
{
RenderDetails rd;   // creating the details

rd.size = 0;    // setting the size to 0

// allocating a small bit of memory
rd.rid = malloc(1024 * sizeof(unsigned int));
rd.vao = malloc(1024 * sizeof(unsigned int));
rd.shader = malloc(1024 * sizeof(unsigned int));
rd.texture = malloc(1024 * sizeof(unsigned int));

return rd;
}

int getRenderDetailsIDIndex(RenderDetails rd, unsigned int rid)
{
if(rd.size > rid)  // if the size is bigger than the ID then it is a valid ID
    if(rd.rid[rid] == rid)  // just in case no manipulation of the table has happened
        return rid;

for (int i = 0; i < rd.size; i++)   // simple linear search
    if(rd.rid[i] == rid)
        return i;
return -1;
}

static void SwapRenderDetails(RenderDetails* rd, unsigned int rid1, unsigned int rid2)
{
int index1 = getRenderDetailsIDIndex(*rd, rid1);
int index2 = getRenderDetailsIDIndex(*rd, rid2);

if(index1 > rd->size || index2 > rd->size)
    {
    printf("\nERROR: Trying to access inaccessable index %d %d", index1, index2);
    exit(1);
    }

// getting temporary stuff
unsigned int tid = rd->rid[index1];
unsigned int tvao = rd->vao[index1];
unsigned int tshader = rd->shader[index1];
unsigned int ttexture = rd->texture[index1];

// setting the swap to the other index
rd->rid[index1] = rd->rid[index2];
rd->vao[index1] = rd->vao[index2];
rd->shader[index1] = rd->shader[index2];
rd->texture[index1] = rd->texture[index2];

// setting the other index to the first temp values
rd->rid[index2] = tid;
rd->vao[index2] = tvao;
rd->shader[index2] = tshader;
rd->texture[index2] = ttexture;
}

static void BubbleSortRenderDetails(RenderDetails* rd);

unsigned int AddRenderDetail(RenderDetails* rd, unsigned int vao, unsigned int shader, unsigned int texture)
{
// static unsigned int id = 0; // a static incrementing counter to set the new ID as
const unsigned int n = rd->size;
unsigned int id = findNextIDAvailable(rd->rid, rd->size);

if(n == 0)   // if the size is 0 then just reinitialise the render details
    *rd = InitialiseRenderDetails(); // reinitialise the render details

SetUniformM4(shader, "view", getM4ID());

// make all the arrays bigger by one to accomodate for the new element

/*
ExpandByOne(&rd->rid, n, sizeof(unsigned int));
ExpandByOne(&rd->vao, n, sizeof(unsigned int));
ExpandByOne(&rd->shader, n, sizeof(unsigned int));
ExpandByOne(&rd->texture, n, sizeof(unsigned int));
*/


// setting all the new details
rd->rid[n] = id;
rd->vao[n] = vao;
rd->shader[n] = shader;
rd->texture[n] = texture;

rd->size++; // increase the number of renderables

return rd->rid[n];
}

void RemoveRenderDetail(RenderDetails *rd, unsigned int rid)
{
int index = getRenderDetailsIDIndex(*rd, rid);  // finding the ID
const unsigned int n = rd->size;

if(index == -1)
    return; // if the index isn't found just quit

if(index == rd->size - 1) goto end;   // hehe the naughty goto

SwapRenderDetails(rd, rd->rid[index], rd->rid[rd->size - 1]);   // swapping around the entries

end:
// glDeleteVertexArrays(1, &rd->vao[n - 1]);
// glDeleteBuffers(1, &VBO);
// glDeleteBuffers(1, &EBO);
// glDeleteProgram(&rd->shader[n - 1]);
// glDeleteTextures(1, &rd->texture[n - 1]);

rd->size--; // decrease the size so it is effectively not there

ShrinkArrayByOne(&rd->rid, n, sizeof(unsigned int));
ShrinkArrayByOne(&rd->vao, n, sizeof(unsigned int));
ShrinkArrayByOne(&rd->shader, n, sizeof(unsigned int));
ShrinkArrayByOne(&rd->texture, n, sizeof(unsigned int));

// To-Do: Could add in a sort here to sort by ID in order to realign the table
}

static unsigned int _CreateRenderable(RenderDetails* rd, unsigned int shape, const char* vsfp, const char* fsfp, const char* texfp)
{
unsigned int vao, vbo, ibo, prog, tex = 0;

viBundle vbund = GetShapeVertices(shape);   // the bundle containing the vertices and count
float* vertices = vbund.vi.vertices;

viBundle ibund = GetShapeIndices(shape);    // the bundle containing the indices and count
unsigned int* indices = ibund.vi.indices;

vao = CreateVAO();  // creating the vao
ibo = CreateIBO(indices, ibund.n); // creating the ibo
BindIBO(ibo);  // binding the ibo to the vao
vbo = CreateVBO(vertices, vbund.n);  // creating the vbo
BindVBO(vbo);  // binding the vbo to the vao

unsigned int ilay[1] = {3};
VAOLayout layout = CreateVertexLayout(ilay, 5, 1);  // setting up the layout to receive
AddToVertexLayout(&layout, 2);  // adding the texture coords to the layout
InitialiseVertexLayout(layout); // initialising the layout to be used

if(!shaderExists(vsfp, fsfp))
    {
    prog = CreateShader(vsfp, fsfp);    // creates the shader object
    AppendToArray(shad_cont.progs, prog);   // add the program to the shader array to enable for reuse
    }
else
    {
    prog = getShader(vsfp, fsfp);
    printf("\nUsing cached");
    }
SetUniformM4(prog, "projection", getProjection(1020, 960, 1));  // setting up the projection

if(texfp != NULL)   // if there is a texture
    {
    tex = CreateTexture(texfp);
    SetUniform1i(prog, "intexture", 0); // set the texture to be used (the 0th active texture)
    }

return AddRenderDetail(rd, vao, prog, tex);
}

unsigned int CreateSpriteRenderable(RenderDetails* rd, const char* spfp, unsigned int sprites, unsigned int sprite)
{
unsigned int shape = SQUARE;
GeneralInitialise(&shape, sprites, sprite, SQUARE);

return _CreateRenderable(rd, shape, "res/texvert.shader", "res/texfrag.shader", spfp);
}

unsigned int CreateSquareRenderable(RenderDetails* rd)
{
unsigned int shape = 0;
GeneralInitialise(&shape, 1, 1, SQUARE);

return _CreateRenderable(rd, shape, "res/vertex.shader", "res/fragment.shader", NULL);
}

unsigned int CreatePlainSquareRenderable(RenderDetails* rd)
{
unsigned int shape = SQUARE;
GeneralInitialise(&shape, 1, 1, SQUARE);

return _CreateRenderable(rd, shape, "res/vertex.shader", "res/fragment.shader", NULL);
}

void DrawRenderable(RenderDetails rds, unsigned int rid)
{
int index = getRenderDetailsIDIndex(rds, rid);
if(index == -1) return; // if it is not found stop

if(rds.texture[index] != 0)
    {
    BindTexture(rds.texture[index]);
    }

BindShader(rds.shader[index]);
BindVAO(rds.vao[index]);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

unsigned int* getRenderablePrograms(RenderDetails rds, unsigned int* rids, int size)
{
unsigned int* progs = (unsigned int*)malloc(size * sizeof(unsigned int));

for (int i = 0; i < size; i++)
    progs[i] = rds.shader[getRenderDetailsIDIndex(rds, rids[i])];  // getting and setting the programs

return progs;
}

void OutputRenderDetails(RenderDetails rds)
{
printf("\nSize: %d", rds.size);
printf("\n\n%32s", "Render Details Table");
printf("\n%-10s%-20s%-13s%-13s\t", "ID", "VAO", "Shader", "Texture");
for (int i = 0; i < rds.size; i++)
    {
    printf("\n%-10d%-20d%-13d%-13d",
        rds.rid[i],
        rds.vao[i],
        rds.shader[i],
        getActiveTexture(rds.texture[i])
        );
    }
}