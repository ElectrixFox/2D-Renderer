#include "BlockOperations.h"
#include "MathsOperations.h"
#include "Array.h"

struct UI_Button {
    int ui_buid;
    int pressed;
};

struct UI_Menu {
    int ui_muid;
    int size;
};

enum UIElement_Type
    {
    BUTTON = 1,
    STATIC_MENU
    // this is the type of element
    };

union UIElement_Details
    {
    // here is where all of the details will be
    struct {
        int pressed;
    }
    Button;

    struct {
        void** items;   // the UI element items
        int size;   // the number of items
        enum UIElement_Type type;   // the type of the items
    } Menu;

    // this should be full of structs for each type of element
    };

struct UIElement
    {
    Array uiids;    // the IDs for the UI elements
    Array trsids;   // the transform ID for this
    
    union UIElement_Details* uidets; // the details for the element
    enum UIElement_Type* eletypes;   // the type of the element
    int size;
    };
typedef struct UIElement UIElement;

void CreateButton(UIElement* eletab, RenderPacket* rp, vec2 position, int scale);

struct UIContainer
    {
    
    };



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
