#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vec2 { float x, y; } vec2;
typedef struct vec3 { float x, y, z; } vec3;

typedef struct mat3 { vec3 mat[3]; } mat3;

typedef float vec4[4];
typedef struct m4 { vec4 mat[4]; } m4;

vec2 LeftCornerFromCentre(vec2 centre, vec2 scale);

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

m4 getProjection(unsigned int wid, unsigned int hig, unsigned int transformed);
m4 GetModelMatrix(vec2 pos, vec2 scale);

m4 getM4ID();

vec2 GetMousePositionRelative(vec2 cursor, unsigned int width, unsigned int height);