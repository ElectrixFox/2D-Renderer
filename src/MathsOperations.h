#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vec3 { float x, y, z; };
typedef struct vec3 vec3;

struct vec2 { float x, y; };
typedef struct vec2 vec2;


float generalisedDot(float u[], float v[], unsigned int n);
float dotprod(vec3 u, vec3 v);

void transposeMatr3(float m[][3], unsigned int n);

void generalisedMatrMult3(float m1[][3], float m2[][3], unsigned int n, unsigned int m);

vec3 applyMatrix(vec3 matr[3], vec3 vec);
void changeVerts(vec3 verts[], vec3 matr[3], unsigned int n);

void TransformObject(vec3 vertices[], vec2 moveBy, unsigned int n);
void ScaleObject(vec3 vertices[], vec2 scale, unsigned int n);