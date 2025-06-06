#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vec2 { float x, y; } vec2;
typedef struct vec3 { float x, y, z; } vec3;

typedef struct mat3 { vec3 mat[3]; } mat3;

typedef float vec4[4];
typedef struct m4 { vec4 mat[4]; } m4;

/**
 * Expands an array
 * 
 * @param arr The actual array
 * @param osize The old size
 * @param nsize The new size to resize to
 * @param elesize Sizeof an element in the array, e.g. if it was an array of integers elesize would be sizeof(int)
 */
void ExpandArray(void** arr, unsigned int osize, unsigned int nsize, unsigned int elesize);

/**
 * Expanda an array by one
 * 
 * @param arr The array
 * @param size The size of the array
 * @param elesize The size of an element in the array
 */
void ExpandByOne(void** arr, const unsigned int size, unsigned int elesize);

/**
 * Appends an element to an array
 * 
 * @param arr The actual array
 * @param size The size of the array
 * @param item The item to add
 * @param elesize The size of the element to add
 */
void AppendToArray(void** arr, unsigned int size, void** item, unsigned int elesize);

vec2 LeftCornerFromCentre(vec2 centre, vec2 scale);

/**
 * Checks if point is in the square at position pos with scale scale
 * 
 * @param point The point to check if it is the square
 * @param pos The position of the centre of the square
 * @param scale The scale of the square
 */
int PointInSquare(vec2 point, vec2 pos, vec2 scale);

float generalisedDot(float u[], float v[], unsigned int n);
float dotprod(vec3 u, vec3 v);

void transposeMatr3(float m[][3], unsigned int n);

void generalisedMatrMult3(float m1[][3], float m2[][3], unsigned int n, unsigned int m);

vec3 applyMatrix(mat3 matr, vec3 vec);
void changeVerts(vec3 verts[], mat3 matr, unsigned int n);

void TransformObject(vec3 vertices[], vec2 moveBy, unsigned int n);
void ScaleObject(vec3 vertices[], vec2 scale, unsigned int n);

m4 mat3Tomat4(mat3 matr);

/**
 * Gets the projection matrix
 * 
 * @param wid The width of the window
 * @param hig The height of the window
 * @param transformed Should the origin be transformed so that it is in the bottom left
 * 
 * @returns 4x4 projection matrix to be passed to the shader
 */
m4 getProjection(unsigned int wid, unsigned int hig, unsigned int transformed);

/**
 * Gets the model matrix for the (square) entity
 * 
 * @param pos The centre of the entity
 * @param scale The scale vector of the entity
 * @note This also gets the bottom left corner of the square within the function
 */
m4 GetModelMatrix(vec2 pos, vec2 scale);

m4 getM4ID();

vec2 GetMousePositionRelative(vec2 cursor, unsigned int width, unsigned int height);