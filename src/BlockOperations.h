#include "Drawable.h"
#include "Block.h"

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
unsigned int _PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BLOCK block, vec2 position);

/**
 * Removes a block at the position
 * 
 * @param rds The rendering table
 * @param tds The transform table
 * @param rid The render ID of the block to remove
 */
void _RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, unsigned int rid);
