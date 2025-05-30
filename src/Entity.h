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

void SetNumberOfSprites(unsigned int* shape, unsigned int numofspr);
void SetActiveSprite(unsigned int* shape, unsigned int sprite);
void SetActiveShape(unsigned int* shape, unsigned int sh);

Entities InitialiseEntities();

/**
 * A function to find an entity in the Entities object
 * 
 * @param es The Entities object containing all the entities
 * @param eid The ID of the entity to find
 * 
 * @returns The index of the entity in the Entities object
 */
unsigned int FindEntityInEntities(Entities es, unsigned int eid);

/**
 * Updates the shader model matrix from the given data
 * 
 * @note This should be turned into a static (private (ish)) function
 * 
 * @param shaders The array of shader programs
 * @param positions Array of positions
 * @param scales Array of scales
 * @param size The number of Entities to update (i.e. the size of each of the arrays for now)
 */
void _UpdateEntities(unsigned int* shaders, vec2* positions, vec2* scales, unsigned int size);

/**
 * Updates the position, scale and other details of the entities for running
 * 
 * @param es The entities to be updated
 */
void UpdateEntities(Entities es);

unsigned int _CreateEntity(Entities* es, unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture);

/**
 * Creates the entity and adds it to the entities
 * 
 * @param es A pointer to the Entities object
 * @param shape The shape to draw (easiest set using the enum SHAPE)
 * @param position The position of the shape
 * @param vshader The file path to the vertex shader
 * @param fshader The file path to the fragment shader
 * @param texture The file path to the texture
 * 
 * @returns The ID of the entity created
 */
unsigned int CreateEntity(Entities* es, unsigned int shape, vec2 position, const char* vshader, const char* fshader, const char* texture);

/**
 * Creates an entity from a sprite sheet and adds it to the Entities object
 * 
 * @param es A pointer to the Entities object
 * @param shape The shape to draw (easiest set using the enum SHAPE)
 * @param position The position of the shape
 * @param sheet The file path to the file sheet
 * @param sprite The sprite to display
 * @param spritenum The number of sprites in the sprite sheet
 * 
 * @returns The ID of the entity created
 */
unsigned int CreateEntityFromSpriteSheet(Entities* es, unsigned int shape, vec2 position, const char* sheet, unsigned int sprite, unsigned int spritenum);

/**
 * Gets the position of the entity
 * 
 * @param es The collection of entities
 * @param eid The ID of the entity to get the position of
 * 
 * @returns The position of the entity
 */
vec2 GetEntityPosition(Entities es, unsigned int eid);

/**
 * Sets the position of the entity
 * 
 * @param es The collection of entities
 * @param eid The ID of the entity to set the position of
 * @param pos The position to set the entity to
 */
void SetEntityPosition(Entities es, unsigned int eid, vec2 pos);

/**
 * Sets a uniform float for an entity
 * 
 * @deprecated This isn't the ideal way to handle entity uniforms
 * 
 * @param es The collection of entities
 * @param eid The ID of the entity to set the uniform for
 * @param varname The name of the uniform
 * @param value The value of the uniform to set
 */
void SetEntityUniformFloat(Entities es, unsigned int eid, const char* varname, float value);

/**
 * Gets the scale of the entity
 * 
 * @param es The collection of entities
 * @param eid The ID of the entity to get the scale of
 * 
 * @returns The scale of the entity
 */
vec2 GetEntityScale(Entities es, unsigned int eid);

/**
 * Sets the scale of the entity
 * 
 * @param es The collection of entities
 * @param eid The ID of the entity to set the scale of
 * @param scale The scale to set the entity to
 */
void SetEntityScale(Entities es, unsigned int eid, vec2 scale);

/**
 * Sets the scale of the entity
 * 
 * @param es The collection of entities
 * @param eid The ID of the entity to set the scale factor of
 * @param scfac The factor which the scale is to be multiplied by
 */
void SetEntityScaleFactor(Entities es, unsigned int eid, float scfac);

/**
 * Sets the colour of the entity
 * 
 * @param es The collection of entities
 * @param eid The ID of the entity to set the colour of
 * @param colour The colour to set the entity as
 */
void SetEntityColour(Entities es, unsigned int eid, vec4 colour);

/**
 * Draws the entity from given data
 * 
 * @note This should be turned into a static (private (ish)) function
 * 
 * @param textures The array of texture OpenGL elements
 * @param shaders The array of shader programs
 * @param vaos Array of vertex array objects
 * @param size The number of Entities to render (i.e. the size of each of the arrays for now)
 */
void _DrawEntities(unsigned int* textures, unsigned int* shaders, unsigned int* vaos, unsigned int size);

/**
 * Draws the entities in es
 * 
 * @param es The Entities object containing all of the entities
 */
void DrawEntities(Entities es);