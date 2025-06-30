#include "SystemUI.h"

const int datsize = 256;

UI_Table InitialiseUI()
{
UI_Table ui;

// initialising all of the memory
ui.ui_id = (unsigned int*)malloc(sizeof(unsigned int));
ui.trsid = (unsigned int*)malloc(sizeof(unsigned int));
ui.trigger = (GUI_ACTION_TRIGGER*)malloc(sizeof(GUI_ACTION_TRIGGER));
ui.action = (ui_act_fun*)malloc(10 * sizeof(ui_act_fun));
ui.data = (void**)malloc(datsize);  // just a constant amount of memory to give

ui.size = 0;

return ui;
}

static void expandUITable(UI_Table* ui)
{
const int n = ui->size;

ExpandByOne(&ui->ui_id, n, sizeof(unsigned int));
ExpandByOne(&ui->trsid, n, sizeof(unsigned int));
ExpandByOne(&ui->trigger, n, sizeof(GUI_ACTION_TRIGGER));
ExpandByOne(&ui->action, n, sizeof(ui_act_fun));
ExpandByOne(&ui->data, n, datsize);

ui->size++; // increasing the size
}

static int findUIIDinTable(UI_Table ui, unsigned int ui_id)
{
for (int i = 0; i < ui.size; i++)   // simple linear search
    if(ui.ui_id[i] == ui_id)
        return i;
return -1;
}

static void addUIRendering(UI_Table* ui, RenderPacket* rp, unsigned int ui_id)
{
}

unsigned int addButton(UI_Table* ui, RenderPacket* rp, vec2 pos, float scale, void* renderInfo)
{
static unsigned int ui_id = 0;
expandUITable(ui);

int index = ui_id;  // temporary and should be replaced with a more optimal function
ui->ui_id[index] = ui_id++;    // set and increase the ID

if(renderInfo == NULL)
    {
    ui->data[index] = (void*)malloc(sizeof(GUI_RENDER_INFO));
    *(GUI_RENDER_INFO*)ui->data[index] = (GUI_RENDER_INFO)0;
    }

int ind = CreateBasicSquare(rp, pos, scale, NULL);  // creates the square
unsigned int trsid = rp->drabs.trsids[ind]; // gets the transformation ID
ui->trsid[index] = trsid;   // sets the new transformation ID

addUIRendering(ui, rp, ui->ui_id[index]);

return ui->ui_id[index];
}

void assignButtonAction(UI_Table* ui, unsigned int ui_id, GUI_ACTION_TRIGGER trigger, ui_act_fun action)
{
int index = findUIIDinTable(*ui, ui_id);

if(index == -1)
    {
    printf("\nError: Could not find %d in the UI table", ui_id);
    exit(1);
    }

ui->trigger[index] = trigger;
ui->action[index] = action;
}

