#include "Drawable.h"
#include "Block.h"

extern const int snap_to_grid;
extern const int grid_size;

/**
 * Outputs the level in matrix form
 * 
 * @param grid The grid returned by the getLevel (or similar) function
 * @param w The width of the grid
 * @param h The height of the grid
 */
void OutputLevel(const int** grid, int w, int h);

/**
 * Reads the level from a file
 * 
 * @param levelfp The file path to the level
 * @param w A pointer to the width of the grid (to be set by the function)
 * @param h A pointer to the height of the grid (to be set by the function)
 * @param grid A pointer to the 2D array which the grid is (set by the function)
 */
void ReadLevel(const char* levelfp, int* w, int* h, int*** grid);

void RenderLevel();

/**
 * Gets the information of where the blocks are
 * 
 * @param rds The render details
 * @param tds The transform details
 * @param drabs The drawable details
 * @param pds The pressable details
 * @param w A pointer to the width (this will be set)
 * @param h A pointer to the height (this will be set)
 * @param grid A pointer to a 2D array of integers (again this will be set)
 */
void getLevel(RenderDetails rds, TransformationDetails tds, Drawables drabs, PressableDetails pds, int* w, int* h, int*** grid);