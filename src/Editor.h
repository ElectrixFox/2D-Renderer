#include "Drawable.h"
#include "Block.h"
#include "Camera.h"
#include "Level.h"

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
 * @param block The block to create
 * @param position Where to create the block
 * 
 * @returns The render ID for the new block
 */
unsigned int PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BLOCK block, vec2 position);

/**
 * Removes a block at the position
 * 
 * @param rds The rendering table
 * @param tds The transform table
 * @param rid The render ID of the block to remove
 */
void RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, unsigned int rid);


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
 * @param drabs The drawable objects table
 * @param trsid The transformation ID of the object
 */
void SelectBlock(Drawables drabs, unsigned int trsid);

/**
 * Applies the view matrix to all render details in the given table
 * 
 * @param cam The camera to apply
 * @param rds The render details containing the shaders
 * 
 * @warning Make sure the right render detail table is passed otherwise things can go very wrong very quickly
 */
void ApplyCamera(Camera cam, RenderDetails rds);

/**
 * Applies the projection matrix to all render details in the given table
 * 
 * @param cam The camera to apply
 * @param rds The render details containing the shaders
 * 
 * @warning Make sure the right render detail table is passed otherwise things can go very wrong very quickly
 */
void ApplyProjection(Camera cam, RenderDetails rds);

#pragma endregion

#pragma region EditorUI
/**
 * Builds the block selection bar
 * 
 * @param rds A pointer to the rendering details
 * @param tds A pointer to the transformation details
 * @param drabs A pointer to the drawable details
 */
void BuildSelectBar(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs);

/**
 * Unfolds the options for the sprite
 * 
 * @param rds The render table
 * @param tds The transform table
 * @param drabs The drawables
 * 
 * @param rid The render ID of the block to unfold sprites for
 */
void UnfoldMoreOptions(RenderDetails rds, TransformationDetails tds, Drawables drabs, unsigned int rid);



#pragma endregion
