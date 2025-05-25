#include "Entity.h"

m4 getEntityModelMatrix4(Entity e)
{
return (m4){
        e.scale.x, 0.0f, 0.0f, e.pos.x,
        0.0f, e.scale.y, 0.0f, e.pos.y,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
};
}

void UpdateEntity(Entity e)
{
const unsigned int prog = e.rdets.shader;  // constant just for safety
BindShader(prog);
SetUniformM4(prog, "model", getEntityModelMatrix4(e)); // getting and setting the model matrix
}

Entity CreateEntity(unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture)
{
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

return (Entity){position, scale, {vao, prog, tex, ibo}};
}

void DrawEntity(Entity e)
{
UpdateEntity(e);
if (e.rdets.texture != 0)
    {
    glActiveTexture(GL_TEXTURE0);
    BindTexture(e.rdets.texture);
    }

BindShader(e.rdets.shader);
BindVAO(e.rdets.vao);
//  the 6 should be changed to the number of indices
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}