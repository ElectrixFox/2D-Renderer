#include "MenuUI.h"

//-----------------------------------------------------------
//------------------------- Globals -------------------------
//-----------------------------------------------------------

static vec2* curpos; // the position of the cursor


void InitialiseCursorPosition(vec2* cpos)
{
curpos = cpos;
}

//-----------------------------------------------------------------------
//------------------------- Rendering Functions -------------------------
//-----------------------------------------------------------------------

void drawGUIElements(RenderPacket gui_rp)
{
DrawDrawables(gui_rp.rds, gui_rp.tds, gui_rp.drabs);
}

//--------------------------------------------------------------------
//------------------------- Action Functions -------------------------
//--------------------------------------------------------------------

static int pressedInRectangle(vec2 pos, vec2 scale)
{

return PointInSquare(*curpos, pos, scale);
}

void hasBeenPressed(GUI_Button button)
{

}

void hoveredOver(GUI_Button button)
{

}

//----------------------------------------------------------------------------
//------------------------- Initialisation Functions -------------------------
//----------------------------------------------------------------------------

GUI_Button CreateButton(RenderPacket* gui_rp, vec2 pos, GUI_ACTION_TRIGGER trigger, void (*action)(int))
{
GUI_Button button;
CreateBasicSquare(gui_rp, pos, 25.0f, NULL);

switch (trigger)    // assigning the action
    {
    case PRESS:
        button.on_click = &action;
        break;
    case HOVER:
        button.on_hover = &action;
    default:
        break;
    }

return button;
}

void CreateMenu(vec2 pos)
{

}


/*
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
*/