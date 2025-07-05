#pragma once
#include "Drawable.h"
#include "Block.h"

#ifndef BLOCK_OPERATIONS_H
#define BLOCK_OPERATIONS_H

/**
 * Creates a block at the position with default scale (25x25)
 * 
 * @param rds The rendering table
 * @param tds The transform table
 * @param block The block information of the block to create
 * @param position Where to create the block
 * 
 * @returns The render ID for the new block
 */
unsigned int _PlaceBlockCustom(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BlockInfo block, vec2 position);

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

unsigned int PlaceImmovableBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, BlockInfo block, vec2 position);

unsigned int UpdateImmovableBlocks(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, const int w, const int h, const int** grid);

#endif