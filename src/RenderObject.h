#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Buffer.h"
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

static unsigned int _CreateRenderable(RenderDetails* rd, unsigned int shape, const char* vsfp, const char* fsfp, const char* texfp);
unsigned int CreateSquareRenderable(RenderDetails* rd);

void DrawRenderable(RenderDetails rds, unsigned int rid);