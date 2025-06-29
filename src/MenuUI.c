#include "MenuUI.h"

//-----------------------------------------------------------------------
//------------------------- Private Definitions -------------------------
//-----------------------------------------------------------------------
typedef void (*bu_act_fun)(int);

typedef struct 
    {
    unsigned int* buid;
    unsigned int* trsid;

    bu_act_fun* on_click_funcs;  // click actions
    bu_act_fun* on_hover_funcs;  // click actions

    int size;
    } GUI_Buttons;

typedef struct
    {
    unsigned int* headids;
    unsigned int* buids;
    unsigned int* sizes;

    unsigned int size;
    } GUI_Menus;

//-----------------------------------------------------------
//------------------------- Globals -------------------------
//-----------------------------------------------------------

RenderPacket* rp;

GUI_Buttons gui_buttons;

//----------------------------------------------------------------------------
//------------------------- Initialisation Functions -------------------------
//----------------------------------------------------------------------------

void InitialiseGUIButtons()
{
gui_buttons.buid = (unsigned int*)malloc(sizeof(unsigned int));
gui_buttons.trsid = (unsigned int*)malloc(sizeof(unsigned int));
gui_buttons.on_click_funcs = (bu_act_fun*)malloc(sizeof(bu_act_fun));
gui_buttons.on_hover_funcs = (bu_act_fun*)malloc(sizeof(bu_act_fun));
gui_buttons.size = 0;
}

void assignGuiRenderPacket(RenderPacket* gui_rp) { rp = gui_rp; }

RenderPacket InitialiseGUI()
{
RenderPacket gui_rp = InitialiseRenderPacket();
InitialiseGUIButtons();

return gui_rp;
}


//-----------------------------------------------------------------------
//------------------------- Rendering Functions -------------------------
//-----------------------------------------------------------------------

void drawGUIElements(RenderPacket gui_rp) { DrawDrawables(gui_rp.rds, gui_rp.tds, gui_rp.drabs); }

//--------------------------------------------------------------------
//------------------------- Action Functions -------------------------
//--------------------------------------------------------------------

static int pressedInRectangle(vec2 pos, vec2 scale)
{
vec2 cpos = getCursorPosition();
return PointInSquare(cpos, pos, scale);
}

int hasBeenPressed(GUI_Button button)
{
int index = getTransformationIDIndex(rp->tds, button.trsid);
return pressedInRectangle(rp->tds.pos[index], rp->tds.scale[index]);
}

int hoveredOver(GUI_Button button)
{
int index = getTransformationIDIndex(rp->tds, button.trsid);
return pressedInRectangle(rp->tds.pos[index], rp->tds.scale[index]);
}

void checkButtons()
{
GLFWwindow* window = getWindow();

if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    for (int i = 0; i < gui_buttons.size; i++)
        {
        int index = getTransformationIDIndex(rp->tds, gui_buttons.trsid[i]);
        if(pressedInRectangle(rp->tds.pos[index], rp->tds.scale[index]))
            {
            gui_buttons.on_click_funcs[i](gui_buttons.buid[i]);
            }
        }
}

//----------------------------------------------------------------------------
//------------------------- Initialisation Functions -------------------------
//----------------------------------------------------------------------------

GUI_Button CreateButton(RenderPacket* gui_rp, vec2 pos, GUI_ACTION_TRIGGER trigger, void (*action)(int), vec4 col)
{
static unsigned int buid = 0;
GUI_Button button;
unsigned int dind = CreateBasicSquare(gui_rp, pos, 25.0f, col);
button.buid = buid++;
button.trsid = gui_rp->drabs.trsids[dind];

switch (trigger)    // assigning the action
    {
    case PRESS:
        button.on_click = action;
        break;
    case HOVER:
        button.on_hover = action;
    default:
        break;
    }

return button;
}


void addGUIButton(GUI_Button button)
{
ExpandByOne(&gui_buttons.buid, gui_buttons.size, sizeof(unsigned int));
ExpandByOne(&gui_buttons.trsid, gui_buttons.size, sizeof(unsigned int));
ExpandByOne(&gui_buttons.on_click_funcs, gui_buttons.size, sizeof(bu_act_fun));
ExpandByOne(&gui_buttons.on_hover_funcs, gui_buttons.size, sizeof(bu_act_fun));

const int n = gui_buttons.size;
gui_buttons.buid[n] = button.buid;
gui_buttons.trsid[n] = button.trsid;
gui_buttons.on_click_funcs[n] = button.on_click;
gui_buttons.on_hover_funcs[n] = button.on_hover;

gui_buttons.size++;
}

GUI_Menu CreateMenu(RenderPacket* gui_rp, vec2 pos, GUI_ACTION_TRIGGER trigger, void (*action)(int))
{
GUI_Menu menu;
menu.head = CreateButton(gui_rp, pos, trigger, action, (vec4){1.0f, 0.62f, 0.0f, 1.0f});
addGUIButton(menu.head);

menu.contents = (GUI_Button*)malloc(sizeof(GUI_Button));
menu.size = 0;

return menu;
}

void addMenuEntry(GUI_Menu* menu, GUI_Button entry)
{
const int stack_menu = 1;  // align the buttons

ExpandByOne(menu->contents, menu->size, sizeof(GUI_Button));
menu->contents[menu->size++] = entry;

if(stack_menu)
    {
    vec2 headPos = getPosition(rp->tds, menu->head.trsid);
    vec2 elepos = {headPos.x, headPos.y - (menu->size + 1) * 25.0f};
    setPosition(rp->tds, entry.trsid, elepos);
    }
}

void addGUIMenu(GUI_Menu menu)
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