#include "oEntity.h"

#ifdef OLD

Entities InitialiseEntities()
{
Entities es;
es.size = 0;
es.ids = malloc(sizeof(unsigned int) * 1);
es.positions = malloc(sizeof(vec2) * 1);
es.scales = malloc(sizeof(vec2) * 1);
es.rdets.shaders = malloc(sizeof(unsigned int) * 1);
es.rdets.textures = malloc(sizeof(unsigned int) * 1);
es.rdets.vaos = malloc(sizeof(unsigned int) * 1);

return es;
}

unsigned int FindEntityInEntities(Entities es, unsigned int eid)
{
for (int i = 0; i < es.size; i++)
    if(es.ids[i] == eid) return i;
}

void _UpdateEntities(unsigned int* shaders, vec2* positions, vec2* scales, unsigned int size)
{
for(int i = 0; i < size; i++)
    {
    // can add constant variables here to reference the variables at the indices, these will probably be taken out by the compiler anyway
    BindShader(shaders[i]);
    SetUniformM4(shaders[i], "model", GetModelMatrix(positions[i], scales[i]));
    }
}

void UpdateEntities(Entities es) { _UpdateEntities(es.rdets.shaders, es.positions, es.scales, es.size); }

unsigned int _CreateEntity(Entities* es, unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture)
{
static unsigned int id = 0;
unsigned int vao, vbo, ibo, prog;
unsigned int tex = 0;
vec2 scale = {1.0f, 1.0f};
viBundle vbund = GetShapeVertices(shape);
float* vertices = vbund.vi.vertices;
viBundle ibund = GetShapeIndices(shape);
unsigned int* indices = ibund.vi.indices;

m4 model = GetModelMatrix(position, scale);

vao = CreateVAO();  // creating the vao
ibo = CreateIBO(indices, ibund.n); // creating the ibo
vbo = CreateVBO(vertices, vbund.n);  // creating the vbo

unsigned int ilay[1] = {3};
VAOLayout layout = CreateVertexLayout(ilay, 5, 1);  // setting up the layout
AddToVertexLayout(&layout, 2);  // adding the texture coords to the layout
InitialiseVertexLayout(layout); // initialising the layout to be used

prog = CreateShader(vshader, fshader);

if(texture != NULL)
    {
    tex = CreateTexture(texture);
    SetUniform1i(prog, "intexture", getActiveTexture(tex)); // set the texture to be used (the 0th active texture)
    }


SetUniformM4(prog, "projection", getProjection(1020, 960, 1));
SetUniformM4(prog, "model", model);

const unsigned int sze = es->size;
ExpandArray(&es->ids, sze, sze + 1, sizeof(unsigned int));
ExpandArray(&es->positions, sze, sze + 1, sizeof(vec2));
ExpandArray(&es->scales, sze, sze + 1, sizeof(vec2));
ExpandArray(&es->rdets.shaders, sze, sze + 1, sizeof(unsigned int));
ExpandArray(&es->rdets.textures, sze, sze + 1, sizeof(unsigned int));
ExpandArray(&es->rdets.vaos, sze, sze + 1, sizeof(unsigned int));

const unsigned int top = es->size;
es->ids[top] = id++;
es->positions[top] = position;
es->scales[top] = scale;
es->rdets.shaders[top] = prog;
es->rdets.textures[top] = tex;
es->rdets.vaos[top] = vao;

return es->ids[top];
}

unsigned int CreateEntity(Entities* es, unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture)
{
SetActiveShape(&shape, shape);
SetActiveSprite(&shape, 1);
SetNumberOfSprites(&shape, 1);

unsigned int id = _CreateEntity(es, shape, position, vshader, fshader, texture);
es->size++;
return id;
}

unsigned int CreateEntityFromSpriteSheet(Entities* es, unsigned int shape, vec2 position, const char* sheet, unsigned int sprite, unsigned int spritenum)
{
// setting up the shape details
SetActiveShape(&shape, shape);
SetActiveSprite(&shape, sprite);
SetNumberOfSprites(&shape, spritenum);

unsigned int id = _CreateEntity(es, shape, position, "res/texvert.shader", "res/texfrag.shader", sheet);

es->size++;
return id;
}

vec2 GetEntityPosition(Entities es, unsigned int eid)
{
for (int i = 0; i < es.size; i++)
    if(es.ids[i] == eid)    // if the correct ID
        return es.positions[i];  // return the position
}

void SetEntityPosition(Entities es, unsigned int eid, vec2 pos)
{
for (int i = 0; i < es.size; i++)
    {
    if(es.ids[i] == eid)    // if the correct ID
        {
        es.positions[i] = pos;  // set the position
        break;
        }
    }
}

void SetEntityUniformFloat(Entities es, unsigned int eid, const char* varname, float value)
{
for (int i = 0; i < es.size; i++)
    {
    if(es.ids[i] == eid)    // if the correct ID
        {
        SetUniform1f(es.rdets.shaders[i], varname, value);
        break;
        }
    }
}

vec2 GetEntityScale(Entities es, unsigned int eid)
{
for (int i = 0; i < es.size; i++)
    if(es.ids[i] == eid)    // if the correct ID
        return es.scales[i];    // return the scale
}

void SetEntityScale(Entities es, unsigned int eid, vec2 scale)
{
for (int i = 0; i < es.size; i++)
    {
    if(es.ids[i] == eid)    // if the correct ID
        {
        es.scales[i] = scale;   // set the scale
        break;
        }
    }
}

void SetEntityScaleFactor(Entities es, unsigned int eid, float scfac)
{
unsigned int index = FindEntityInEntities(es, eid);
es.scales[index].x *= scfac;
es.scales[index].y *= scfac;
}

void SetEntityColour(Entities es, unsigned int eid, vec4 colour)
{
for (int i = 0; i < es.size; i++)
    {
    if(es.ids[i] == eid)    // if the correct ID
        {
        SetUniform4f(es.rdets.shaders[i], "colour", colour);    // set the colour
        break;
        }
    }
}

void _DrawEntities(unsigned int* textures, unsigned int* shaders, unsigned int* vaos, unsigned int size)
{
// for (int i = 0; i < size; i++)
for (int i = size - 1; 0 <= i; i--)
    {
    if(textures[i] != 0)
        {
        BindTexture(textures[i]);
        }
    BindShader(shaders[i]);
    BindVAO(vaos[i]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void DrawEntities(Entities es) { _DrawEntities(es.rdets.textures, es.rdets.shaders, es.rdets.vaos, es.size); }

#endif