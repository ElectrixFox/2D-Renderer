// #include "BlockOperations.h"
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
    unsigned int buid;
    unsigned int trsid;

    void (*on_click)(int);  // click action
    void (*on_hover)(int);  // hover action
    } GUI_Button;

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


GUI_Button CreateButton(RenderPacket* gui_rp, vec2 pos, GUI_ACTION_TRIGGER trigger, void (*action)(int));

void addGUIButton(GUI_Button button);

void CreateMenu(vec2 pos);

#endif
