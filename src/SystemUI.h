
#ifndef SYSTEMUI_H
#define SYSTEMUI_H

#pragma once
#include "Drawable.h"
#include "Input.h"
#include "Array.h"

typedef enum
    {
    PRESS,
    HOVER
    } GUI_ACTION_TRIGGER;

typedef void (*ui_act_fun)(int);

typedef enum
    {
    DEFAULT_SQUARE = 0
    } GUI_RENDER_INFO;

struct UI_Table
    {
    unsigned int* ui_id;    // primary key
    unsigned int* trsid;    // foreign key to link to transform

    GUI_ACTION_TRIGGER* trigger;    // the triggers
    ui_act_fun* action; // the actions
    
    // the first part of the data for each element should be an indicator to what it contains and its size
    void** data;    // the data for each element

    int size;   // the number of entries
    };
typedef struct UI_Table UI_Table;

/**
 * Initialises the UI and allocates memory
 * 
 * @returns A new UI table containing all of the information
 */
UI_Table InitialiseUI();

/**
 * Creates a button at the given position with the given details
 * 
 * @param ui A pointer to the UI table
 * @param rp A pointer to the render packet for the UI
 * @param pos The position of the button
 * @param scale The scale factor of the square for the button
 * @param renderInfo The information to be used to initialise the button
 * 
 * @returns The ID of the new UI element
 */
unsigned int addButton(UI_Table* ui, RenderPacket* rp, vec2 pos, float scale, void* renderInfo);

void assignButtonAction(UI_Table* ui, unsigned int ui_id, GUI_ACTION_TRIGGER trigger, ui_act_fun action);

int hasBeenPressed(UI_Table ui, RenderPacket rp, unsigned int ui_id);

int hoveredOver(UI_Table ui, RenderPacket rp, unsigned int ui_id);

void checkUI(UI_Table ui, RenderPacket rp);

#endif