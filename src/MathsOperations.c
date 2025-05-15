#include "MathsOperations.h"

float generalisedDot(float u[], float v[], unsigned int n)
{
float res = 0;  // setting up the result

for(int i = 0; i < n; i++)
    {
    res += u[i] * v[i]; // doing the dotting
    }

return res;
}

float dotprod(vec3 u, vec3 v)
{
float tu[3] = {u.x, u.y, u.z}; 
float tv[3] = {v.x, v.y, v.z}; 

float res = 0;

for (int i = 0; i < 3; i++)
    {
    res += tu[i] * tv[i];
    }

return res;
}

void transposeMatr3(float m[][3], unsigned int n)
{
float** res = (float*)malloc(sizeof(float) * n * n);  // setting up the result matrix

for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        res[i][j] = m[j][i];    // doing the transposing

for (int i = 0; i < n; i++)
    strcpy(m[i], res[i]);   // copying into the input

}

void generalisedMatrMult3(float m1[][3], float m2[][3], unsigned int n, unsigned int m)
{
transposeMatr3(m2, 3);  // transposing the matrix

for (int i = 0; i < n; i++)
    {
    generalisedDot(m1[i], m2[i], n);    // getting the entries
    }
}

vec3 applyMatrix(vec3 matr[3], vec3 vec)
{
vec3 res;

res.x = dotprod(matr[0], (vec3){vec.x, vec.y, vec.z});
res.y = dotprod(matr[1], (vec3){vec.x, vec.y, vec.z});
res.z = dotprod(matr[2], (vec3){vec.x, vec.y, vec.z});

return res;
}

void changeVerts(vec3 verts[], vec3 matr[3], unsigned int n)
{
for (int i = 0; i < n; i++)
    {
    verts[i] = applyMatrix(matr, verts[i]); // applying the transformation
    }
}

void TransformObject(float vertices[], float moveBy[2], unsigned int n)
{
vec3 matr[3] = {
    { 1.0f, 0.0f, moveBy[0] },
    { 0.0f, 1.0f, moveBy[1] },
    { 0.0f, 0.0f, 1.0f }
};

vec3* verts = (vec3*)malloc(sizeof(float) * n * sizeof(vec3));
for (int i = 0; i < n; i++)
    {
    verts[i] = (vec3){vertices[0 + 3 * i], vertices[1 + 3 * i], vertices[2 + 3 * i]};   // setting the vec3 vertices
    }


changeVerts(verts, matr, n);

for (int i = 0; i < n; i++)
    {
    vertices[0 + 3 * i] = verts[i].x;
    vertices[1 + 3 * i] = verts[i].y;
    vertices[2 + 3 * i] = verts[i].z;
    }
}