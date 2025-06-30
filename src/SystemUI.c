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
ui.data = (RenderInformation*)malloc(sizeof(RenderInformation));    // just a constant amount of memory to give

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

unsigned int getUITransform(UI_Table ui, unsigned int ui_id) { return ui.trsid[findUIIDinTable(ui, ui_id)]; }

static void addUIRendering(UI_Table* ui, RenderPacket* rp, unsigned int ui_id)
{
}

static void UnpackRenderInfo(void* renderInfo)
{

}

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
else// if(rendinf.ssi.spfp != NULL)   // if there is a file path
    {
    ui->data[index].ssi = rendinf.ssi;
    unsigned int rid = CreateSpriteRenderable(&rp->rds, rendinf.ssi.spfp, rendinf.ssi.nosp, rendinf.ssi.spr);
    unsigned int trsid = AddTransformation(&rp->tds, pos, (vec2){scale, scale});
    AddDrawable(&rp->drabs, trsid, rid);

    ind = findDrawablesRenderable(rp->drabs, rid);
    }

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
    if(ui.trigger[i] != (GUI_ACTION_TRIGGER)HOVER)  // if is not hover then skip
        continue;
    
    if(isCursorOnUIElement(ui, rp, ui.ui_id[i]))
        {
        printf("\nPerforming hover action for %d", ui.ui_id[i]);
        ui.action[i](ui.ui_id[i]);
        }
    }


if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    for (int i = 0; i < ui.size; i++)
        {
        if(ui.trigger[i] != (GUI_ACTION_TRIGGER)0)   // if it is not press then continue
            continue;

        if(isCursorOnUIElement(ui, rp, ui.ui_id[i]))
            {
            printf("\nPerforming action for %d", ui.ui_id[i]);
            ui.action[i](ui.ui_id[i]);
            }
        }
}
