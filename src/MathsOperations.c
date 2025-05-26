#include "MathsOperations.h"

void ExpandArray(void* arr, unsigned int osize, unsigned int nsize, unsigned int elesize)
{
void* nptr = malloc(elesize * osize); // allocating the new memory
nptr = realloc(arr, elesize * nsize);  // making the array bigger
arr = nptr;    // setting the old array to the new bigger one
}

void AppendToArray(void* arr, unsigned int size, void* item, unsigned int elesize)
{
ExpandArray(arr, size, size + 1, elesize);
memcpy((&arr)[size], item, elesize);
// memmove(((int*)arr + size) * elesize, item, elesize);
}

vec2 LeftCornerFromCentre(vec2 centre, vec2 scale)
{
vec2 pos;
pos.x = centre.x - scale.x / 2;
pos.y = centre.y - scale.y / 2;
return pos;
}

int PointInSquare(vec2 point, vec2 pos, vec2 scale)
{
if (abs(point.x - pos.x) < scale.x)
    if (abs(point.y - pos.y) < scale.y)
        return 1;

return 0;
}

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
float** res = (float**)malloc(sizeof(float) * n * n);  // setting up the result matrix

for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        res[i][j] = m[j][i];    // doing the transposing

for (int i = 0; i < n; i++)
    memcpy(m[i], res[i], sizeof(m[i]) / sizeof(m[0][0]));   // copying into the input

}

void generalisedMatrMult3(float m1[][3], float m2[][3], unsigned int n, unsigned int m)
{
transposeMatr3(m2, 3);  // transposing the matrix

for (int i = 0; i < n; i++)
    {
    generalisedDot(m1[i], m2[i], n);    // getting the entries
    }
}

vec3 applyMatrix(mat3 matr, vec3 vec)
{
vec3 res;

res.x = dotprod(matr.mat[0], (vec3){vec.x, vec.y, vec.z});
res.y = dotprod(matr.mat[1], (vec3){vec.x, vec.y, vec.z});
res.z = dotprod(matr.mat[2], (vec3){vec.x, vec.y, vec.z});

return res;
}

void changeVerts(vec3 verts[], mat3 matr, unsigned int n)
{
for (int i = 0; i < n; i++)
    {
    verts[i] = applyMatrix(matr, verts[i]); // applying the transformation
    }
}

void TransformObject(vec3 vertices[], vec2 moveBy, unsigned int n)
{
mat3 matr = {
    (vec3){ 1.0f, 0.0f, moveBy.x },
    { 0.0f, 1.0f, moveBy.y },
    { 0.0f, 0.0f, 1.0f }
};

changeVerts(vertices, matr, n);
}

void ScaleObject(vec3 vertices[], vec2 scale, unsigned int n)
{
mat3 matr = {
    (vec3){ scale.x, 0.0f, 0.0f },
    { 0.0f, scale.y, 0.0f },
    { 0.0f, 0.0f, 1.0f }
};

changeVerts(vertices, matr, n);
}

m4 mat3Tomat4(mat3 matr)
{
return (m4){
    matr.mat[0].x, matr.mat[0].y, matr.mat[0].z, 0.0f,
    matr.mat[1].x, matr.mat[1].y, matr.mat[1].z, 0.0f,
    matr.mat[2].x, matr.mat[2].y, matr.mat[2].z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};
}

m4 getProjection(unsigned int wid, unsigned int hig, unsigned int transformed)
{
return 
    (m4){
         2 / (float)wid, 0.0f, 0.0f, -(float)(transformed),
         0.0f, 2 / (float)hig, 0.0f, -(float)(transformed),
         0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
    };
}

m4 GetModelMatrix(vec2 pos, vec2 scale)
{
vec2 transformed = LeftCornerFromCentre(pos, scale);
return (m4){
        scale.x, 0.0f, 0.0f, transformed.x,
        0.0f, scale.y, 0.0f, transformed.y,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
};
}

m4 getM4ID()
{
return (m4){
    {1.0f, 0.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f, 0.0f,
     0.0f, 0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 0.0f, 1.0f}
};
}

vec2 GetMousePositionRelative(vec2 cursor, unsigned int width, unsigned int height)
{
return (vec2){cursor.x, height - cursor.y};
}
