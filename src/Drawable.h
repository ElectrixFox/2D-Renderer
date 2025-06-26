#pragma once
#include "Entity.h"

struct Drawables {
    unsigned int* trsids;
    unsigned int* rids;
    unsigned int size;
};
typedef struct Drawables Drawables;

Drawables InitialiseDrawables();

void AddDrawable(Drawables* drabs, unsigned int trid, unsigned int rid);

/**
 * Finds the index of the given transform ID in the drawables table
 * 
 * @param drabs The drawables table
 * @param trid The transform ID to find
 * 
 * @returns -1 if not found and the index otherwise
 */
int findDrawablesTransform(Drawables drabs, unsigned int trid);

/**
 * Finds the index of the given render ID in the drawables table
 * 
 * @param drabs The drawables table
 * @param rid The render ID to find
 * 
 * @returns -1 if not found and the index otherwise
 */
int findDrawablesRenderable(Drawables drabs, unsigned int rid);

/**
 * Gets the render IDs from an array of transform IDs
 * 
 * @param drabs The drawables table
 * @param trids The transformation IDs to find in the drawables
 * @param size The number of IDs
 * 
 * @returns An array of renderable IDs
 */
unsigned int* getRenderIDsFromTransformIDs(Drawables drabs, unsigned int* trids, unsigned int size);

void RemoveDrawable(Drawables* drabs, RenderDetails* rds, TransformationDetails* tds, unsigned int trid);

void UpdateImmovables(TransformationDetails* tds, Drawables* drabs);

void DrawDrawables(RenderDetails rds, TransformationDetails tds, Drawables drabs);

/**
 * Outputs the drawables table
 * 
 * @param drabs The table of drawables
 */
void OutputDrawables(Drawables drabs);

struct RenderPacket
    {
    Drawables drabs;
    RenderDetails rds;
    TransformationDetails tds;
    };
typedef struct RenderPacket RenderPacket;
