#include "Drawable.h"
#include "PressableObject.h"
#include "Block.h"

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
 */
void PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds, BLOCK block, vec2 position);

/**
 * Removes a block at the position
 * 
 * @param rds The rendering table
 * @param tds The transform table
 * @param prds The pressable table
 * @param prid The render ID of the block to remove
 */
void RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds, unsigned int rid);

void ReadLevel(const char* levelfp);

void RenderLevel();

/**
 * Builds the block selection bar
 * 
 * @param rds A pointer to the rendering details
 * @param tds A pointer to the transformation details
 * @param drabs A pointer to the drawable details
 * @param prds A pointer to the pressable details
 */
void BuildSelectBar(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, PressableDetails* prds);

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