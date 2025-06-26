#include "BlockOperations.h"
#include "MathsOperations.h"
#include "Array.h"

enum UI_TYPES {
    UI_BUTTON = 1,
    UI_DROPDOWNMENU
    };
typedef enum UI_TYPES UI_TYPES;

struct Buttons
    {
    
    };

struct DropDown_Menu
    {
    void** items;   // the actual items
    int itsize; // the size of one item
    int size;   // the number of items

    int dropped;    // has the menu been dropped down

    unsigned int icon;

    vec2 position;  // where is the menu
    };
typedef struct DropDown_Menu DropDown_Menu;



DropDown_Menu CreateDropDownMenu(RenderPacket* rp, vec2 position, int icon, int sizeoftype);

void addToMenu(RenderPacket* rp, DropDown_Menu* dmu, void* item);

void toggleDropMenu(RenderPacket* rp, DropDown_Menu* dmu);
