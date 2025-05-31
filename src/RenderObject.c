#include "RenderObject.h"

RenderDetails InitialiseRenderDetails()
{
RenderDetails rd;   // creating the details

rd.size = 0;    // setting the size to 0

// allocating a small bit of memory
rd.rid = (unsigned int*)malloc(sizeof(unsigned int));
rd.vao = (unsigned int*)malloc(sizeof(unsigned int));
rd.shader = (unsigned int*)malloc(sizeof(unsigned int));
rd.texture = (unsigned int*)malloc(sizeof(unsigned int));

return rd;
}

int getRenderDetailsIDIndex(RenderDetails rd, unsigned int rid)
{
if(rd.rid[rid] == rid)  // just in case no manipulation of the table has happened
    return rid;

for (int i = 0; i < rd.size; i++)   // simple linear search
    if(rd.rid[i] == rid)
        return i;
return -1;
}

unsigned int AddRenderDetail(RenderDetails *rd, unsigned int vao, unsigned int shader, unsigned int texture)
{
static unsigned int id = 0; // a static incrementing counter to set the new ID as
const unsigned int n = rd->size;

// make all the arrays bigger by one to accomodate for the new element
ExpandByOne(&rd->vao, n, sizeof(unsigned int));
ExpandByOne(&rd->shader, n, sizeof(unsigned int));
ExpandByOne(&rd->texture, n, sizeof(unsigned int));

// setting all the new details
rd->rid[n] = id++;  // increment the ID counter too
rd->vao[n] = vao;
rd->shader[n] = shader;
rd->texture[n] = texture;

return rd->rid[n];
}

void RemoveRenderDetail(RenderDetails *rd, unsigned int rid)
{
int index = getRenderDetailsIDIndex(*rd, rid);  // finding the ID

if(index == -1)
    return; // if the index isn't found just quit

if(index == rd->size)
    goto end;   // hehe the naughty goto

// getting temporary stuff
unsigned int tid = rd->rid[index];
unsigned int tvao = rd->vao[index];
unsigned int tshader = rd->shader[index];
unsigned int ttexture = rd->texture[index];

// setting the to delete to the end values
rd->rid[index] = rd->rid[rd->size];
rd->vao[index] = rd->vao[rd->size];
rd->shader[index] = rd->shader[rd->size];
rd->texture[index] = rd->texture[rd->size];

// setting the end to the thing to delete
rd->rid[rd->size] = tid;
rd->vao[rd->size] = tvao;
rd->shader[rd->size] = tshader;
rd->texture[rd->size] = ttexture;

end:
rd->size--; // decrease the size so it is effectively not there

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
vbo = CreateVBO(vertices, vbund.n);  // creating the vbo

unsigned int ilay[1] = {3};
VAOLayout layout = CreateVertexLayout(ilay, 5, 1);  // setting up the layout to receive
AddToVertexLayout(&layout, 2);  // adding the texture coords to the layout
InitialiseVertexLayout(layout); // initialising the layout to be used

prog = CreateShader(vsfp, fsfp);    // creates the shader object

if(texfp != NULL)   // if there is a texture
    {
    tex = CreateTexture(texfp);
    SetUniform1i(prog, "intexture", getActiveTexture(tex)); // set the texture to be used (the 0th active texture)
    }

return AddRenderDetail(rd, vao, prog, tex);
}

unsigned int CreateSquareRenderable(RenderDetails* rd)
{
unsigned int shape = 0;
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