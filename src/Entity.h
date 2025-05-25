#include "RenderObject.h"

struct Entity
{
vec2 pos;
vec2 scale;
viobject rdets;
};

// a renderable needs vertices, a vao and shader
// an object needs position and scale 

typedef struct Entity Entity;

m4 getEntityModelMatrix4(Entity e);

void UpdateEntity(Entity e);

Entity CreateEntity(unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture);
void DrawEntity(Entity e);