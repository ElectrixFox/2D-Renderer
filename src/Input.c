#include "Input.h"

static int ckey = 0;    // current key
static int caction = 0; // current action
static int cmods = 0;   // current mod keys

GLFWwindow* wind;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
wind = window;

ckey = key;
caction = action;
cmods = mods;
}

void InitialiseInput(GLFWwindow *window)
{
glfwSetKeyCallback(window, key_callback);   // setting up the callback
wind = window;
}

InputPacket getCurrentInputInformation()
{
return (InputPacket){ckey, caction, cmods};
}

void resetInputPacket()
{
ckey = -1;
caction = -1;
cmods = -1;
}

int isPressedSingle(int key)
{
static int pkey = 0;
InputPacket ip = getCurrentInputInformation();

if(glfwGetKey(getWindow(), key) == GLFW_PRESS)
    {
    glfwWaitEventsTimeout(0.1f);
    return 1;
    }
else
    {
    return 0;
    }

return 0;
}

int isHeldDown(int key)
{
InputPacket ip = getCurrentInputInformation();
if(ip.key == key)
    if(ip.action == GLFW_REPEAT)
        return 1;
return 0;
}

vec2 _getCursorPosition(GLFWwindow* window)
{
double x, y;
int wid, hig;
glfwGetCursorPos(window, &x, &y);
glfwGetWindowSize(window, &wid, &hig);
vec2 point = GetMousePositionRelative((vec2){(float)x, (float)y}, wid, hig);

return point;
}

vec2 getCursorPosition() { return _getCursorPosition(wind); } 

int* _getPressedwScale(vec2* poses, vec2* scales, int size, vec2 cpos)
{
int* indices = (int*)malloc(2 * sizeof(int));
int top = 1;

for (int i = 0; i < size; i++)
    {
    if(PointInSquare(cpos, poses[i], scales[i]))
        {
        indices[top] = i;
        ExpandByOne(&indices, top, sizeof(int));
        top++;
        }
    }

indices[0] = top - 1;   // setting the size of the array

return indices;
}


int* _getPressed(vec2* poses, int size, vec2 cpos)
{
int* indices = (int*)malloc(2 * sizeof(int));
int top = 1;

for (int i = 0; i < size; i++)
    {
    if(PointInSquare(cpos, poses[i], (vec2){25.0f, 25.0f}))
        {
        indices[top] = i;
        ExpandByOne(&indices, top, sizeof(int));
        top++;
        }
    }

indices[0] = top - 1;   // setting the size of the array

return indices;
}


int* _getPressedArea(vec2* poses, int size, vec2 curpos, float range)
{
int* indices = (int*)malloc(2 * sizeof(int));
int top = 1;

for (int i = 0; i < size; i++)
    if(abs(poses[i].x - curpos.x) < range && abs(poses[i].y - curpos.y) < range)
        {
        indices[top] = i;
        ExpandByOne(&indices, top, sizeof(int));
        top++;
        }

indices[0] = top - 1;   // setting the size of the array

return indices;
}

int* getPressedArea(vec2* poses, int size, float range)
{
return _getPressedArea(poses, size, getCursorPosition(), range);
}

GLFWwindow* getWindow() { return wind; }

#pragma region Input Table

extern InputTable ip;

void handle_input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
if(action == GLFW_PRESS)
    ip.keys[key] = 1;
else if(action == GLFW_RELEASE)
    ip.keys[key] = 0;

ip.action = action;
ip.mods = 0x1111 ^ mods;
}


InputTable InitialiseInputTable(GLFWwindow* window)
{
InputTable ipt;

// initialising all of the arrays to 0
calloc(ipt.keys, 1024);
ipt.action = 0;
ipt.mods = 0;

glfwSetKeyCallback(window, handle_input);   // setting up the callback
wind = window;

return ipt;
}


void addToInputTable(InputTable* ipt, int key, int mods, int action)
{

}

int checkInput(int key, int mods, int action)
{
return (ip.keys[key] == 1 && (ip.mods & mods) != 0 && ip.action == action);
}

int isPressedSingleKey(int key)
{
static int pkey = 0;

if(ip.keys[key] == 1 && ip.keys[pkey] == 0)
    {
    printf("\nPressed");
    pkey = key;
    return 1;
    }
else if(ip.keys[key] == 0)
    {
    printf("\nReleased");
    pkey = key;
    return 0;
    }

/*
if(ip.keys[key] == 1)
    {
    if(ip.action == GLFW_PRESS)
        {
        printf("\nPressed");
        pkey = key;
        return 1;
        }
    else if(ip.action == GLFW_RELEASE)
        {
        printf("\nReleased");
        pkey = -1;
        return 0;
        }
    }
*/

return 0;
}

#pragma endregion