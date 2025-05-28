#include "RenderObject.h"

struct Entities
    {
    unsigned int* ids;
    vec2* positions;
    vec2* scales;
    viobject rdets;
    unsigned int size;
    };
typedef struct Entities Entities;

struct Entity
{
unsigned int id;
vec2 pos;
vec2 scale;
viobject rdets;
};

typedef enum SHAPE
    {
    SQUARE = 0,
    } SHAPE;

// a renderable needs vertices, a vao and shader
// an object needs position and scale 

typedef struct Entity Entity;

vec2 PositionToEntitySpace(Entity e);

m4 getEntityModelMatrix4(Entity e);

Entities InitialiseEntities();

void _UpdateEntities(unsigned int* shaders, vec2* positions, vec2* scales, unsigned int size);
void UpdateEntities(Entities es);

unsigned int _CreateEntity(Entities* es, unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture);

/**
 * Creates the entity and adds it to the entities
 * 
 * @returns The ID of the entity created
 */
unsigned int CreateEntity(Entities* es, unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture);

vec2 GetEntityPosition(Entities es, unsigned int eid);
void SetEntityPosition(Entities es, unsigned int eid, vec2 pos);

void SetEntityUniformFloat(Entities es, unsigned int eid, const char* varname, float value);

vec2 GetEntityScale(Entities es, unsigned int eid);
void SetEntityScale(Entities es, unsigned int eid, vec2 scale);

void SetEntityColour(Entities es, unsigned int eid, vec4 colour);

void _DrawEntities(unsigned int* textures, unsigned int* shaders, unsigned int* vaos, unsigned int size);
void DrawEntities(Entities es);