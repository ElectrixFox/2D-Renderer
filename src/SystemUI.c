#include "SystemUI.h"

const int datsize = 256;

UI_Trigger_Action_Table InitialiseUITriggerActions()
{
UI_Trigger_Action_Table ta;

// initialising all of the memory
ta.ui_id = (unsigned int*)malloc(sizeof(unsigned int));
ta.action = (ui_act_fun*)malloc(10 * sizeof(ui_act_fun));
ta.size = 0;

return ta;
}

UI_Table InitialiseUI()
{
UI_Table ui;

// initialising all of the memory
ui.ui_id = (unsigned int*)malloc(sizeof(unsigned int));
ui.trsid = (unsigned int*)malloc(sizeof(unsigned int));

for (int i = 0; i < UI_NO_TRIGGERS; i++)    // initialising the trigger actions
    ui.actions[i] = InitialiseUITriggerActions();

ui.data = (RenderInformation*)malloc(sizeof(RenderInformation));
ui.size = 0;

return ui;
}

static void expandUITriggerActionTable(UI_Trigger_Action_Table* ta)
{
const int n = ta->size;

ExpandByOne(&ta->action, n, sizeof(ui_act_fun));
ExpandByOne(&ta->ui_id, n, sizeof(unsigned int));

ta->size++;
}

static void expandUITable(UI_Table* ui)
{
const int n = ui->size;

ExpandByOne(&ui->ui_id, n, sizeof(unsigned int));
ExpandByOne(&ui->trsid, n, sizeof(unsigned int));
ExpandByOne(&ui->data, n, datsize);

ui->size++; // increasing the size
}

static int findUITriggerActionIDinTable(UI_Trigger_Action_Table ta, unsigned int ui_id)
{
for (int i = 0; i < ta.size; i++)   // simple linear search
    if(ta.ui_id[i] == ui_id)
        return i;
return -1;
}

static int findUIIDinTable(UI_Table ui, unsigned int ui_id)
{
for (int i = 0; i < ui.size; i++)   // simple linear search
    if(ui.ui_id[i] == ui_id)
        return i;
return -1;
}

unsigned int getUITransform(UI_Table ui, unsigned int ui_id) { return ui.trsid[findUIIDinTable(ui, ui_id)]; }

RenderInformation getUIRenderInformation(UI_Table ui, unsigned int ui_id) { return ui.data[findUIIDinTable(ui, ui_id)]; }

unsigned int addButton(UI_Table* ui, RenderPacket* rp, vec2 pos, float scale, RenderInformation rendinf)
{
static unsigned int ui_id = 0;
expandUITable(ui);

int index = ui_id;  // temporary and should be replaced with a more optimal function
ui->ui_id[index] = ui_id++;    // set and increase the ID

int ind = -1;
if(rendinf.rinf == (GUI_RENDER_INFO)NULL)
    {
    ui->data[index].rinf = (GUI_RENDER_INFO)0;
    ind = CreateBasicSquare(rp, pos, scale, NULL);  // creates the square
    }
else if(rendinf.ssi.spfp != NULL)   // if there is a file path
    {
    ui->data[index].ssi = rendinf.ssi;
    unsigned int rid = CreateSpriteRenderable(&rp->rds, rendinf.ssi.spfp, rendinf.ssi.nosp, rendinf.ssi.spr);
    unsigned int trsid = AddTransformation(&rp->tds, pos, (vec2){scale, scale});
    ind = AddDrawable(&rp->drabs, trsid, rid);
    }

unsigned int trsid = rp->drabs.trsids[ind]; // gets the transformation ID
ui->trsid[index] = trsid;   // sets the new transformation ID

return ui->ui_id[index];
}

void addUITriggerAction(UI_Trigger_Action_Table* ta, unsigned int ui_id, ui_act_fun action)
{
expandUITriggerActionTable(ta);

int index = ta->size - 1;  // temporary and should be replaced with a more optimal function
ta->ui_id[index] = ui_id;
ta->action[index] = action;
}

void assignUITriggerAction(UI_Trigger_Action_Table* ta, unsigned int ui_id, ui_act_fun action)
{
int index = findUITriggerActionIDinTable(*ta, ui_id);

if(index == -1)
    {
    addUITriggerAction(ta, ui_id, action);
    }
else
    ta->action[index] = action;
}

void assignButtonAction(UI_Table* ui, unsigned int ui_id, GUI_ACTION_TRIGGER trigger, ui_act_fun action)
{
int index = findUIIDinTable(*ui, ui_id);

if(index == -1)
    {
    printf("\nError: Could not find %d in the UI table", ui_id);
    exit(1);
    }

assignUITriggerAction(&ui->actions[trigger], ui_id, action);
}

static int pressedInRectangle(vec2 pos, vec2 scale)
{
vec2 cpos = getCursorPosition();
return PointInSquare(cpos, pos, scale);
}

static int isCursorOnUIElement(UI_Table ui, RenderPacket rp, unsigned int ui_id)
{
int index = findUIIDinTable(ui, ui_id);
vec2 pos = getPosition(rp.tds, ui.trsid[index]);
vec2 scale = getScale(rp.tds, ui.trsid[index]);
return pressedInRectangle(pos, scale);
}

void checkUI(UI_Table ui, RenderPacket rp)
{
GLFWwindow* window = getWindow();



for (int i = 0; i < ui.size; i++)
    {
    int index = findUITriggerActionIDinTable(ui.actions[HOVER], ui.ui_id[i]);
    if(index == -1) // if there is no hover action then skip
        continue;
    
    if(isCursorOnUIElement(ui, rp, ui.ui_id[i]))
        {
        printf("\nPerforming hover action for %d", ui.ui_id[i]);
        ui.actions[HOVER].action[index](ui.ui_id[i]);
        }
    }


if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
    for (int i = 0; i < ui.size; i++)
        {
        int index = findUITriggerActionIDinTable(ui.actions[PRESS], ui.ui_id[i]);
        if(index == -1) // if there is no hover action then skip
            continue;
        
        if(isCursorOnUIElement(ui, rp, ui.ui_id[i]))
            {
            printf("\nPerforming action for %d", ui.ui_id[i]);
            ui.actions[PRESS].action[index](ui.ui_id[i]);
            }
        }
    }
}
