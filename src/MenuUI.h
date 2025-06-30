// #include "BlockOperations.h"
#define GUI_SYSTEM
#ifndef GUI_SYSTEM
#define GUI_SYSTEM

#pragma once
#include "Drawable.h"
#include "MathsOperations.h"
#include "Input.h"
#include "Array.h"

//--------------------------------------------------------------------
//------------------------- Enum Definitions -------------------------
//--------------------------------------------------------------------

typedef enum
    {
    PRESS,
    HOVER
    } GUI_ACTION_TRIGGER;

//----------------------------------------------------------------------
//------------------------- Struct Definitions -------------------------
//----------------------------------------------------------------------

typedef struct 
    {
    unsigned int buid;
    unsigned int trsid;

    void (*on_click)(int);  // click action
    void (*on_hover)(int);  // hover action
    } GUI_Button;

typedef struct
    {
    GUI_Button head;

    GUI_Button* contents;
    int size;
    } GUI_Menu; // what is a menu but just a collection of buttons within a list?

//----------------------------------------------------------------------------
//------------------------- Initialisation Functions -------------------------
//----------------------------------------------------------------------------

void assignGuiRenderPacket(RenderPacket* gui_rp);

RenderPacket InitialiseGUI();

//-----------------------------------------------------------------------
//------------------------- Rendering Functions -------------------------
//-----------------------------------------------------------------------

void drawRectangle();

void drawGUIElements(RenderPacket gui_rp);

//--------------------------------------------------------------------
//------------------------- Action Functions -------------------------
//--------------------------------------------------------------------

int hasBeenPressed(GUI_Button button);

int hoveredOver(GUI_Button button);

void checkButtons();

//----------------------------------------------------------------------------
//------------------------- Initialisation Functions -------------------------
//----------------------------------------------------------------------------


GUI_Button CreateButton(RenderPacket* gui_rp, vec2 pos, GUI_ACTION_TRIGGER trigger, void (*action)(int), vec4 col);

void addGUIButton(GUI_Button button);

GUI_Menu CreateMenu(RenderPacket* gui_rp, vec2 pos, GUI_ACTION_TRIGGER trigger, void (*action)(int));

void addMenuEntry(GUI_Menu* menu, GUI_Button entry);

void addGUIMenu(GUI_Menu menu);

#endif
