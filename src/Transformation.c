#include "Transformation.h"

TransformationDetails InitialiseTransformationDetails(unsigned int width, unsigned int height)
{
TransformationDetails tds;  // creating the details

tds.size = 0;  // setting the size to 0

// allocating a small bit of memory
tds.trsid = (unsigned int*)malloc(sizeof(unsigned int));
tds.pos = (vec2*)malloc(sizeof(vec2));
tds.scale = (vec2*)malloc(sizeof(vec2));

// setting up the width height pointers
tds.width = width;
tds.height = height;

return tds;
}

int getTransformationIDIndex(TransformationDetails tds, unsigned int trsid)
{
if(tds.size > trsid)    // if the size is bigger than the ID then it is a valid ID
    if(tds.trsid[trsid] == trsid)   // just in case no manipulation of the table has happened
        return trsid;

for (int i = 0; i < tds.size; i++)  // simple linear search
    if(tds.trsid[i] == trsid)
        return i;
return -1;
}

unsigned int AddTransformation(TransformationDetails *tds, vec2 pos, vec2 scale)
{
static unsigned int id = 0; // a static incrementing counter to set the new ID as
const unsigned int n = tds->size;

// make all the arrays bigger by one to accomodate for the new element
ExpandByOne(&tds->trsid, n, sizeof(unsigned int));
ExpandByOne(&tds->pos, n, sizeof(vec2));
ExpandByOne(&tds->scale, n, sizeof(vec2));


// setting all the new details
tds->trsid[n] = id++;   // increment the ID counter too
tds->pos[n] = pos;
tds->scale[n] = scale;

tds->size++;    // increase the number of transforms

return tds->trsid[n];
}

void RemoveTransformation(TransformationDetails *tds, unsigned int tid)
{
int index = getTransformationIDIndex(*tds, tid); // finding the ID

if(index == -1)
    return; // if the index isn't found just quit

if(index == tds->size - 1) goto end;   // hehe the naughty goto

// getting temporary stuff
unsigned int tmpid = tds->trsid[index];
vec2 tpos = tds->pos[index];
vec2 tscale = tds->scale[index];

// setting the to delete to the end values
tds->trsid[index] = tds->trsid[tds->size - 1];
tds->pos[index] = tds->pos[tds->size - 1];
tds->scale[index] = tds->scale[tds->size - 1];

// setting the end to the thing to delete
tds->trsid[tds->size - 1] = tmpid;
tds->pos[tds->size - 1] = tpos;
tds->scale[tds->size - 1] = tscale;

end:
tds->size--;    // decrease the size so it is effectively not there

// To-Do: Could add in a sort here to sort by ID in order to realign the table
}

void setPosition(TransformationDetails tds, unsigned int trsid, vec2 newpos)
{
int index = getTransformationIDIndex(tds, trsid);   // find the ID
if(index == -1) return; // if not found return
tds.pos[index] = newpos;    // setting the new position
}

vec2 getPosition(TransformationDetails tds, unsigned int trsid) { return tds.pos[getTransformationIDIndex(tds, trsid)]; }

void setScale(TransformationDetails tds, unsigned int trsid, vec2 newscale)
{
int index = getTransformationIDIndex(tds, trsid);   // find the ID
if(index == -1) return; // if not found return
tds.scale[index] = newscale;    // setting the new scale
}

vec2 getScale(TransformationDetails tds, unsigned int trsid) { return tds.scale[getTransformationIDIndex(tds, trsid)]; }

m4 getTransformModelMatrix(TransformationDetails tds, unsigned int tid)
{
int index = getTransformationIDIndex(tds, tid); // find the transformation ID
if(index != -1)
    return GetModelMatrix(tds.pos[index], tds.scale[index]);    // get the model matrix

return getM4ID();   // return the identity so nothing bad goes on
}

void getTransformModelMatrices(TransformationDetails tds, m4* models)
{
const int n = tds.size; // for ease of use
models = (m4*)malloc(n * sizeof(m4));   // allocating the memory to be used

for (int i = 0; i < n; i++)
    models[i] = GetModelMatrix(tds.pos[i], tds.scale[i]);   // doing the calculation and setting the value
}

m4 getTransformProjectionMatrix(TransformationDetails tds) { return getProjection(tds.width, tds.height, 1); }

int CheckPressed(TransformationDetails tds, unsigned int tid, vec2 cursorpos)
{
unsigned int index = getTransformationIDIndex(tds, tid); // some hash function to get where the eid is in the big array

if(PointInSquare(cursorpos, tds.pos[index], tds.scale[index]))
    return 1;
return 0;
}

