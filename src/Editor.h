#include "Drawable.h"
#include "Block.h"
#include "Level.h"
#include "Camera.h"

#pragma region Main

/**
 * A function to read the level
 * 
 * A function to render the level
 * 
 * A function to build the item select bar
 * 
 */

/**
 * Creates a block at the position with default scale (25x25)
 * 
 * @param rds The rendering table
 * @param tds The transform table
 * @param prds The pressables table
 * @param block The block to create
 * @param position Where to create the block
 * 
 * @returns The render ID for the new block
 */
unsigned int PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds, BLOCK block, vec2 position);

/**
 * Removes a block at the position
 * 
 * @param rds The rendering table
 * @param tds The transform table
 * @param prds The pressable table
 * @param prid The render ID of the block to remove
 */
void RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds, unsigned int rid);

/**
 * Builds the block selection bar
 * 
 * @param rds A pointer to the rendering details
 * @param tds A pointer to the transformation details
 * @param drabs A pointer to the drawable details
 * @param prds A pointer to the pressable details
 */
void BuildSelectBar(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds, Camera* cam);

/**
 * Gets the currently selected block (the block to be placed)
 * 
 * @returns The block type to be created
 */
BLOCK getActiveBlock();

/**
 * Sets the block to be created
 * 
 * @param block The block which should be used when blocks are created
 */
void setActiveBlock(BLOCK block);

/**
 * Selects the block type to be placed
 * 
 * @param prds The pressable details table
 * @param drabs The drawable objects table
 */
void SelectBlock(PressableDetails prds, Drawables drabs, unsigned int prid);


void ApplyCamera(Camera cam, PressableDetails prds, Drawables drabs, TransformationDetails trds, RenderDetails rds);

void ApplyStaticCamera(Camera cam, PressableDetails prds, Drawables drabs, TransformationDetails trds, RenderDetails rds);

void SetSprite(RenderDetails* rd, unsigned int rid);

#pragma endregion

#pragma region Levels

#ifndef LEVELS

/**
 * Draws the level to the screen
 * 
 * @param rds The rendering table
 * @param tds The transform table
 * @param drabs The drawables table
 * @param prds The pressables table
 * @param w The width of the grid
 * @param h The height of the grid
 * @param grid The actual grid (a 2D array of integers)
 */
void DrawLevel(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds, int w, int h, const int** grid);

#endif

#pragma endregion