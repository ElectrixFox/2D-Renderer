#include "Entity.h"

vec2 PositionToEntitySpace(Entity e) { return LeftCornerFromCentre(e.pos, e.scale); }

m4 getEntityModelMatrix4(Entity e) { return GetModelMatrix(e.pos, e.scale); }

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

unsigned int _CreateEntity(Entities es, unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture)
{
static unsigned int id = 0;
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


SetUniformM4(prog, "projection", getProjection(1020, 960, 1));
SetUniformM4(prog, "model", model);

const unsigned int sze = es.size;
ExpandArray(es.ids, sze, sze + 1, sizeof(unsigned int));
ExpandArray(es.positions, sze, sze + 1, sizeof(vec2));
ExpandArray(es.scales, sze, sze + 1, sizeof(vec2));
ExpandArray(es.rdets.shaders, sze, sze + 1, sizeof(unsigned int));
ExpandArray(es.rdets.textures, sze,  + 1, sizeof(unsigned int));
ExpandArray(es.rdets.vaos, sze, sze + 1, sizeof(unsigned int));


const unsigned int top = es.size;
es.ids[top] = id++;
es.positions[top] = position;
es.scales[top] = scale;
es.rdets.shaders[top] = prog;
es.rdets.textures[top] = tex;
es.rdets.vaos[top] = vao;

return es.ids[top];
}

unsigned int CreateEntity(Entities* es, unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture)
{
unsigned int id = _CreateEntity(*es, shape, position, vshader, fshader, texture);
es->size++;
return id;
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
for (int i = 0; i < size; i++)
    {
    if(textures[i] != 0)
        {
        glActiveTexture(GL_TEXTURE0);
        BindTexture(textures[i]);
        }
    BindShader(shaders[i]);
    BindVAO(vaos[i]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void DrawEntities(Entities es) { _DrawEntities(es.rdets.textures, es.rdets.shaders, es.rdets.vaos, es.size); }
