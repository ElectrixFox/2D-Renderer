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
unsigned int _PlaceBlockCustom(RenderPacket* rp, BlockInfo block, vec2 position);

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
unsigned int PlaceBlock(RenderPacket* rp, BLOCK block, vec2 position);

/**
 * Removes a block at the position
 * 
 * @param rds The rendering table
 * @param tds The transform table
 * @param rid The render ID of the block to remove
 */
void RemoveBlock(RenderPacket* rp, unsigned int rid);

/**
 * Rotates a given block by theta degrees
 * 
 * @param rp A pointer to the render packet
 * @param rid The render ID for the block to rotate
 * @param theta The angle (in radians) to rotate the block by
 */
void RotateBlock(RenderPacket* rp, unsigned int rid, float theta);

BLOCK_IM_STATE getImmovableType(const int w, const int h, const int** grid, vec2 pos);

unsigned int PlaceImmovableBlock(RenderPacket* rp, BlockInfo block, vec2 position);

unsigned int UpdateImmovableBlocks(RenderPacket* rp, const int w, const int h, const int** grid);

#endif