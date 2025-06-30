
#ifndef SYSTEMUI_H
#define SYSTEMUI_H

#pragma once
#include "Drawable.h"
#include "Input.h"
#include "Array.h"

typedef enum
    {
    PRESS,
    HOVER,
    UI_NO_TRIGGERS
    } GUI_ACTION_TRIGGER;

typedef void (*ui_act_fun)(int);

typedef enum
    {
    DEFAULT_SQUARE = 1
    } GUI_RENDER_INFO;

union RenderInformation
    {
    SpriteSheetInfo ssi;    // sprite sheet information if it is a sprite sheet
    GUI_RENDER_INFO rinf;   // an enum to say if it is a basic shape
    };
typedef union RenderInformation RenderInformation;

struct UI_Trigger_Action_Table
    {
    unsigned int* ui_id;
    ui_act_fun* action; // the actions for this trigger
    int size;
    };
typedef struct UI_Trigger_Action_Table UI_Trigger_Action_Table;


struct UI_Table
    {
    unsigned int* ui_id;    // primary key
    unsigned int* trsid;    // foreign key to link to transform

    UI_Trigger_Action_Table actions[UI_NO_TRIGGERS];  // array of all different actions, since indexed by action it should be easy to find the correct ones
    
    // the first part of the data for each element should be an indicator to what it contains and its size
    RenderInformation* data;    // the data for each element

    int size;   // the number of entries
    };
typedef struct UI_Table UI_Table;

/**
 * Initialises the UI triggers and allocates memory
 * 
 * @returns A new UI trigger table containing all of the actions
 */
UI_Trigger_Action_Table InitialiseUITriggerActions();


/**
 * Initialises the UI and allocates memory
 * 
 * @returns A new UI table containing all of the information
 */
UI_Table InitialiseUI();

/**
 * Gets the transform ID for the given UI element
 * 
 * @param ui The UI table
 * @param ui_id The ID of the UI element
 * 
 * @returns The transform ID for the UI element
 */
unsigned int getUITransform(UI_Table ui, unsigned int ui_id);

/**
 * Gets the render information for the given UI element
 * 
 * @param ui The UI table
 * @param ui_id The ID of the UI element
 * 
 * @returns The render information for the UI element
 */
RenderInformation getUIRenderInformation(UI_Table ui, unsigned int ui_id);

/**
 * Creates a button at the given position with the given details
 * 
 * @param ui A pointer to the UI table
 * @param rp A pointer to the render packet for the UI
 * @param pos The position of the button
 * @param scale The scale factor of the square for the button
 * @param rendinf The information to be used to initialise the button
 * 
 * @returns The ID of the new UI element
 */
unsigned int addButton(UI_Table* ui, RenderPacket* rp, vec2 pos, float scale, RenderInformation rendinf);

/**
 * Assigns an action to a button which is performed when the trigger happens
 * 
 * @param ui A pointer to the UI table
 * @param ui_id The ID of the UI element to assign the action to
 * @param trigger The trigger for the action
 * @param action A pointer to a function for the action
 */
void assignButtonAction(UI_Table* ui, unsigned int ui_id, GUI_ACTION_TRIGGER trigger, ui_act_fun action);

/**
 * Checks and performs the relevant actions on the UI elements according to their triggers
 * 
 * @param ui The UI table
 * @param rp The render packet for the UI
 */
void checkUI(UI_Table ui, RenderPacket rp);

#endif