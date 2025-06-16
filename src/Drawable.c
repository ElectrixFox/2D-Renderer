#include "Drawable.h"

Drawables InitialiseDrawables()
{
Drawables drabs;
drabs.size = 0;

drabs.trsids = (unsigned int*)malloc(sizeof(unsigned int));
drabs.rids = (unsigned int*)malloc(sizeof(unsigned int));

return drabs;
}

void AddDrawable(Drawables* drabs, unsigned int trid, unsigned int rid)
{
const unsigned int n = drabs->size;

// make all the arrays bigger by one to accomodate for the new element
ExpandByOne(&drabs->rids, n, sizeof(unsigned int));
ExpandByOne(&drabs->trsids, n, sizeof(unsigned int));

// setting all the new details
drabs->rids[n] = rid;
drabs->trsids[n] = trid;

drabs->size++;    // increase the number of drawables
}

int findDrawablesTransform(Drawables drabs, unsigned int trid)
{
for (int i = 0; i < drabs.size; i++)
    if (drabs.trsids[i] == trid) // if the ID matches
        return i; // return the index
return -1; // if the ID isn't found return -1
}

int findDrawablesRenderable(Drawables drabs, unsigned int rid)
{
for (int i = 0; i < drabs.size; i++)
    if (drabs.rids[i] == rid) // if the ID matches
        return i; // return the index
return -1; // if the ID isn't found return -1
}

void RemoveDrawable(Drawables* drabs, RenderDetails* rds, TransformationDetails* tds, unsigned int trid)
{
int index = findDrawablesTransform(*drabs, trid); // finding the ID

if(index == -1)
    return; // if the index isn't found just quit

RemoveRenderDetail(rds, drabs->rids[index]); // remove the render detail from the render details object
RemoveTransformation(tds, drabs->trsids[index]); // remove the transformation from the transformation details object

if(index == drabs->size - 1) goto end;   // hehe the naughty goto

// getting temporary stuff
unsigned int tmp_trsid = drabs->trsids[index];
unsigned int tmp_rid = drabs->rids[index];

// setting the to delete to the end values
drabs->trsids[index] = drabs->trsids[drabs->size - 1];
drabs->rids[index] = drabs->rids[drabs->size - 1];

// setting the end to the thing to delete
drabs->trsids[drabs->size - 1] = tmp_trsid;
drabs->rids[drabs->size - 1] = tmp_rid;

end:
drabs->size--;    // decrease the size so it is effectively not there
}

void DrawDrawables(RenderDetails rds, TransformationDetails tds, Drawables drabs, Camera cam)
{
// getting all we will need from the transformation objects first
m4 view = getCameraMatrix(cam);
m4 projection = getTransformProjectionMatrix(tds);
m4* models = (m4*)malloc(drabs.size * sizeof(m4));  // getting all of the transformation matrices

for (int i = 0; i < drabs.size; i++)    // setting the model matrices
    models[i] = getTransformModelMatrix(tds, drabs.trsids[i]);

// now do the rendering
for (int i = 0; i < drabs.size; i++)    // setting all the uniforms
    {
    const unsigned int prog = rds.shader[getRenderDetailsIDIndex(rds, drabs.rids[i])];  // may as well make this a constant here for efficiency
    SetUniformM4(prog, "model", models[i]);
    SetUniformM4(prog, "view", view);
    SetUniformM4(prog, "projection", projection);
    }

for (int i = 0; i < drabs.size; i++)
    DrawRenderable(rds, drabs.rids[i]); // finally do the actual drawing
}

void OutputDrawables(Drawables drabs)
{
printf("\n\n%20s", "Drawables Table");
printf("\n%-14s%-14s", "Transform ID", "Render ID");
for (int i = 0; i < drabs.size; i++)
    {
    printf("\n%-14d%-14d",
        drabs.trsids[i],
        drabs.rids[i]);
    }
}