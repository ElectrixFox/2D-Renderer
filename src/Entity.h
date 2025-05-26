#include "RenderObject.h"

struct Entity
{
unsigned int id;
vec2 pos;
vec2 scale;
viobject rdets;
};

// a renderable needs vertices, a vao and shader
// an object needs position and scale 

typedef struct Entity Entity;

vec2 PositionToEntitySpace(Entity e);

m4 getEntityModelMatrix4(Entity e);

void UpdateEntities(unsigned int* shaders, vec2* positions, vec2* scales, unsigned int size);
void UpdateEntity(Entity e);

Entity CreateEntity(unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture);

void DrawEntities(unsigned int* textures, unsigned int* shaders, unsigned int* vaos, unsigned int size);
void DrawEntity(Entity e);

typedef struct EntityQueue
    {
    int head, tail;
    Entity* data;
    unsigned int size;
    } EntityQueue;

EntityQueue InitQueueEntityQueue(unsigned int size);

int isEmptyEntityQueue(EntityQueue queue);
int isFullEntityQueue(EntityQueue queue);

void EnqueueEntityQueue(EntityQueue* q, Entity item);
Entity DequeueEntityQueue(EntityQueue* q);
Entity PeekEntityQueue(EntityQueue q);
