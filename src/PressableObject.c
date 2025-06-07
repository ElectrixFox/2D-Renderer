#include "PressableObject.h"

PressableDetails InitialisePressableDetails()
{
PressableDetails prds;

prds.size = 0;

prds.prid = (unsigned int*)malloc(sizeof(unsigned int));
prds.trsid = (unsigned int*)malloc(sizeof(unsigned int));
prds.pract = (unsigned int*)malloc(sizeof(unsigned int));

return prds;
}

int getPressableIDIndex(PressableDetails prds, unsigned int prid)
{
if (prds.size > prid)
    if (prds.prid[prid] == prid)
        return prid;

for (int i = 0; i < prds.size; i++)
    if (prds.prid[i] == prid)
        return i;
return -1;
}

int findPressableTransfom(PressableDetails prds, unsigned int trid)
{
if (prds.size > trid)
    if (prds.trsid[trid] == trid)
        return trid;

for (int i = 0; i < prds.size; i++)
    if (prds.trsid[i] == trid)
        return i;
return -1;
}

unsigned int AddPressable(PressableDetails* prds, unsigned int tid, unsigned int pract)
{
static unsigned int id = 0;
const unsigned int n = prds->size;

ExpandByOne(&prds->prid, n, sizeof(unsigned int));
ExpandByOne(&prds->trsid, n, sizeof(unsigned int));
ExpandByOne(&prds->pract, n, sizeof(unsigned int));

prds->prid[n] = id++;
prds->trsid[n] = tid;
prds->pract[n] = pract;

prds->size++;

return prds->prid[n];
}

void RemovePressable(PressableDetails* prds, unsigned int prid)
{
int index = getPressableIDIndex(*prds, prid);

if (index == -1)
    return;

if (index == prds->size - 1) goto end;

unsigned int tmpid = prds->prid[index];
unsigned int ttrid = prds->trsid[index];
unsigned int tpact = prds->pract[index];

prds->prid[index] = prds->prid[prds->size - 1];
prds->trsid[index] = prds->trsid[prds->size - 1];
prds->pract[index] = prds->pract[prds->size - 1];

prds->prid[prds->size - 1] = tmpid;
prds->trsid[prds->size - 1] = ttrid;
prds->pract[prds->size - 1] = tpact;

end:
prds->size--;
}


int _CheckPressed(vec2* poses, vec2* scales, vec2 cursorpos, unsigned int eid)
{
unsigned int index = eid; // some hash function to get where the eid is in the big array

if(PointInSquare(cursorpos, poses[index], scales[index]))
    return 1;
return 0;
}

int PressedAnother(PressableDetails* prds, TransformationDetails* trds, vec2 curpos)
{
int total = 0;  // total things pressed
for (int i = 0; i < trds->size; i++)
    if(CheckPressed(*trds, trds->trsid[i], curpos)) // checking if anything has been pressed
        total++;

return (total == 1) ? 0 : 1;    // if the total is one then not pressed another, else it has
}

void SetPressableAction(PressableDetails* prds, unsigned int prid, unsigned int pract)
{
int index = getPressableIDIndex(*prds, prid);   // finding the object
prds->pract[index] = pract; // setting the action
}