#include "Drawable.h"

/**
 * A function to read the level
 * 
 * A function to render the level
 * 
 * A function to build the item select bar
 * 
 */

enum BLOCK {
    PLAYER = 0,
    MOVABLE_BLOCK = 1
};
typedef enum BLOCK BLOCK;

/**
 * Creates a block at the position with default scale (25x25)
 * 
 * @param rds The rendering table
 * @param tds The transform table
 * @param ents The entities table
 */
void PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, Entities* ents, BLOCK block, vec2 position);

/**
 * Removes a block at the position
 * 
 * @param rds The rendering table
 * @param tds The transform table
 * @param ents The entities table
 * @param position The position of the block to remove
 */
void RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, Entities* ents, unsigned int eid);

void ReadLevel(const char* levelfp);

void RenderLevel();

void BuildSelectBar(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, Entities* ents);