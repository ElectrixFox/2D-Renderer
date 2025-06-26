#include "MenuUI.h"

DropDown_Menu CreateDropDownMenu(RenderPacket* rp, vec2 position, int icon, int sizeoftype)
{
DropDown_Menu dmu;

// setting known values
dmu.dropped = 1;
dmu.itsize = sizeoftype;
dmu.position = position;
dmu.icon = icon;

// Do something here to render the icon


dmu.items = (void**)malloc(2 * sizeoftype); // allocating a bit of memory
}

void addToMenu(RenderPacket* rp, DropDown_Menu* dmu, void* item)
{
ExpandByOne(dmu->items, dmu->size, dmu->itsize);    // expanding the array
dmu->items[dmu->size] = item;   // setting the new item
dmu->size++;    // increasing the size
}

static void dropMenu(DropDown_Menu* dmu)
{

}

static void foldMenu(DropDown_Menu* dmu)
{

}

void toggleDropMenu(RenderPacket* rp, DropDown_Menu* dmu)
{
if(dmu->dropped == 0)
    dropMenu(dmu);
else
    foldMenu(dmu);
}