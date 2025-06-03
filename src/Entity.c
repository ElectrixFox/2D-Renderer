#include "Entity.h"

Entities InitialiseEntities()
{
Entities ents; // creating the details

ents.size = 0;  // setting the size to 0

// allocating a small bit of memory
ents.eid = (unsigned int*)malloc(sizeof(unsigned int));
ents.rid = (unsigned int*)malloc(sizeof(unsigned int));
ents.trsid = (unsigned int*)malloc(sizeof(unsigned int));
ents.pid =(unsigned int*)malloc(sizeof(unsigned int));

return ents;
}

int getEntitiesIDIndex(Entities ents, unsigned int eid)
{
if(ents.eid[eid] == eid)    // just in case no manipulation of the table has happened
    return eid;

for (int i = 0; i < ents.size; i++) // simple linear search
    if(ents.eid[i] == eid)
        return i;
return -1;
}

unsigned int AddEntity(Entities *ents, unsigned int rid, unsigned int trsid, unsigned int pid)
{
static unsigned int id = 0; // a static incrementing counter to set the new ID as
const unsigned int n = ents->size;

// make all the arrays bigger by one to accomodate for the new element
ExpandByOne(&ents->eid, n, sizeof(unsigned int));
ExpandByOne(&ents->rid, n, sizeof(unsigned int));
ExpandByOne(&ents->trsid, n, sizeof(unsigned int));
ExpandByOne(&ents->pid, n, sizeof(unsigned int));


// setting all the new details
ents->eid[n] = id++;    // increment the ID counter too
ents->rid[n] = rid;
ents->trsid[n] = trsid;
ents->pid[n] = pid;

ents->size++;   // increases the size of the entitys

return ents->eid[n];
}

void RemoveEntity(Entities *ents, unsigned int eid)
{
int index = getEntitiesIDIndex(*ents, eid); // finding the ID

if(index == -1)
    return; // if the index isn't found just quit

const unsigned int size = ents->size;   // constant just for ease of reading

if(index == size)
    goto end;   // hehe the naughty goto

// getting temporary stuff
unsigned int teid = ents->eid[index];
unsigned int trid = ents->rid[index];
unsigned int ttrsid = ents->trsid[index];
unsigned int tpid = ents->pid[index];

// setting the to delete to the end values
ents->eid[index] = ents->eid[size];
ents->rid[index] = ents->rid[size];
ents->trsid[index] = ents->trsid[size];
ents->pid[index] = ents->pid[size];

// setting the end to the thing to delete
ents->eid[size] = teid;
ents->rid[size] = trid;
ents->trsid[size] = ttrsid;
ents->pid[size] = tpid;

end:
ents->size--;    // decrease the size so it is effectively not there

// To-Do: Could add in a sort here to sort by ID in order to realign the table
}


unsigned int CreateEntity(Entities* ent, unsigned int rid, unsigned int tid) { return AddEntity(ent, rid, tid, 0); }

