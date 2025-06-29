// #include "BlockOperations.h"
#ifndef GUI_SYSTEM
#define GUI_SYSTEM

#pragma once
#include "Drawable.h"
#include "MathsOperations.h"
#include "Array.h"

//--------------------------------------------------------------------
//------------------------- Enum Definitions -------------------------
//--------------------------------------------------------------------

typedef enum
    {
    PRESS,
    HOVER
    } GUI_ACTION_TRIGGER;

typedef struct 
    {
    unsigned int trsid;

    void (*on_click)(int);  // click action
    void (*on_hover)(int);  // hover action
    } GUI_Button;

//-----------------------------------------------------------------------
//------------------------- Rendering Functions -------------------------
//-----------------------------------------------------------------------

void drawRectangle();

void drawGUIElements(RenderPacket gui_rp);

//--------------------------------------------------------------------
//------------------------- Action Functions -------------------------
//--------------------------------------------------------------------

void hasBeenPressed();


//----------------------------------------------------------------------------
//------------------------- Initialisation Functions -------------------------
//----------------------------------------------------------------------------


GUI_Button CreateButton(RenderPacket* gui_rp, vec2 pos, GUI_ACTION_TRIGGER trigger, void (*action)(int));

void CreateMenu(vec2 pos);

#endif
