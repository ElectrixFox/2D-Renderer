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
static unsigned int id = 0; // a static incrementing counter to set the new ID as
const unsigned int n = drabs->size;

// make all the arrays bigger by one to accomodate for the new element
ExpandByOne(&drabs->rids, n, sizeof(unsigned int));
ExpandByOne(&drabs->trsids, n, sizeof(unsigned int));

// setting all the new details
drabs->rids[n] = rid;
drabs->trsids[n] = trid;

drabs->size++;    // increase the number of drawables
}

void RemoveDrawable(Drawables* drabs, unsigned int trid)
{
int index = getTransformationIDIndex(*tds, tid); // finding the ID

if(index == -1)
    return; // if the index isn't found just quit

if(index == tds->size)
    goto end;   // hehe the naughty goto

// getting temporary stuff
unsigned int tmpid = tds->trsid[index];
vec2 tpos = tds->pos[index];
vec2 tscale = tds->scale[index];

// setting the to delete to the end values
tds->trsid[index] = tds->trsid[tds->size];
tds->pos[index] = tds->pos[tds->size];
tds->scale[index] = tds->scale[tds->size];

// setting the end to the thing to delete
tds->trsid[tds->size] = tmpid;
tds->pos[tds->size] = tpos;
tds->scale[tds->size] = tscale;

end:
tds->size--;    // decrease the size so it is effectively not there
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